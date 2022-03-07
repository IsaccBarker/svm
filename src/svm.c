#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <assert.h>

#include <svm_const.h>
#include <svm_globals.h>
#include <svm_class.h>
#include <svm_class_file.h>
#include <svm_log.h>

void invalid_command_argument(char* o, char* arg, char* hint) {
    if (hint == NULL) {
        fprintf(stderr, "svm: malformed argument for option `%s`: %s\n", o, arg);
    }

    fprintf(stderr, "svm: malformed argument for option `%s`: %s (hint: %s)\n", o, arg, hint);
}

void print_help_message() {
    printf("Usage: " SVM_NAME " [options]"
            "Options:"
            "\t--help -h <none>: Print this help message.\n"
            "\t--version -V: Print the version of this software.\n"
            "\t--class -c <jvm class file>: Specify the class file to run.\n"
            "\t--verbosity -v <integer>: Specify the verbosity level\n"
            "\t                              1-6, 0 = fatal, 1 = error... 6 = trace.\n"
            "\t                              Must be compiled with verbosity to specify.\n"
            "Home page, report bugs to: https://github.com/IsaccBarker/svm\n");
}

void print_version_message() {
    printf(SVM_NAME " " SVM_VERSION "\n"
            "Copyright (C) 2022 Milo Banks (Isacc/Grey Barker)\n"
            "License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>\n"
            "This is free software: you are free to change and redistribute it.\n"
            "There is NO WARRANTY, to the extent permitted by law.\n"
    );
}

int main(int argc, char *argv[]) {
    int c;
    unsigned int class_file_length = 0;
    char* class_file = "\0";
    unsigned int verbosity = 0;

    while (1) {
        int option_index = 0;
        static struct option long_options[] = {
            {"class", required_argument, 0, 'c'},
            {"help", no_argument, 0, 'h'},
            {"version", no_argument, 0, 'V'},
            {"verbosity", required_argument, 0, 'v'},
            {0, 0, 0, 0}
        };

        c = getopt_long(argc, argv, "hVv:c:",
                    long_options, &option_index);

        if (c == -1) { break; }

        switch (c) {
            case 0: {
                if (long_options[option_index].flag != 0)
                    break;

                printf("option %s", long_options[option_index].name);

                if (optarg)
                    printf(" with arg %s", optarg);

                puts("\n");

                break;
            }

            case 'h': {
                print_help_message();

                exit(EXIT_SUCCESS);
            }

            case 'V': {
                print_version_message();

                exit(EXIT_SUCCESS);
            }

            case 'v': {
                verbosity = strtoul(optarg, NULL, 10);

                if (verbosity == 0 && optarg[0] != '0') {
                    invalid_command_argument("-v", optarg, "value should be unsigned integer");

                    exit(EXIT_FAILURE);
                }

                // This shouldn't ever happen (refering to the 0 catch).
                if (verbosity < 0) verbosity = 0;
                if (verbosity > 6) verbosity = 6;

                break;
            }

            case 'c': {
                char ideal_extension[5] = "class";
                class_file = optarg;

                do {
                    class_file_length++;
                } while (class_file[class_file_length] != '\0');

                for (unsigned int i = class_file_length-sizeof(ideal_extension); i < class_file_length; i++) {
                    if (ideal_extension[i-(class_file_length-sizeof(ideal_extension))] != class_file[i]) {
                        invalid_command_argument("-c", optarg, "file should end in .class.");

                        exit(EXIT_FAILURE);
                    }
                }

                break;
            }

            case '?': {
                // Getopt already printed a message.

                break;
            }
        }
    }

    /* Print any remaining command line arguments (not options). */
    if (optind < argc) {
        fprintf(stderr, "%s: unknown elements (svm does not use subcommands): ", SVM_NAME);
        while (optind < argc)
            fprintf(stderr, "\n\t%s", argv[optind++]);

        fprintf(stderr, "\n%s: this is not a fatal error, these excess elements will be ignored.\n", SVM_NAME);
    }

    if (class_file[0] == '\0') {
        fprintf(stderr, "%s: no class file was specified.\n", SVM_NAME);

        return EXIT_FAILURE;
    }

    log_set_level(6-verbosity);

    // Horray!
    log_trace("Reading class file.");
    FILE* f = get_file_handle(class_file);
    size_t file_length = get_file_size(f);
    unsigned char* data = read_class_file(file_length, f);

    log_trace("Parsing class representation (dumping when complete).");
    if (verbosity == 6) {
        display_class_hex(data, file_length);
    }

    class_representation* rep = parse_class_file(file_length, data);
    print_class_overview(rep);

    return EXIT_SUCCESS;
}
