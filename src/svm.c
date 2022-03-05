#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <assert.h>

#include <svm_const.h>
#include <svm_globals.h>
#include <svm_file.h>
#include <svm_class.h>
#include <svm_class_file.h>

void svm_invalid_command_argument(char* o, char* arg, char* hint) {
    if (hint == NULL) {
        fprintf(stderr, "svm: malformed argument for option `%s`: %s\n", o, arg);
    }

    fprintf(stderr, "svm: malformed argument for option `%s`: %s (hint: %s)\n", o, arg, hint);
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
            {0, 0, 0, 0}
        };

        c = getopt_long (argc, argv, "v:c:",
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

            case 'v': {
                verbosity = strtoul(optarg, NULL, 10);

                if (verbosity == 0 && optarg[0] != '0') {
                    svm_invalid_command_argument("-v", optarg, "value should be unsigned integer");

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
                        svm_invalid_command_argument("-c", optarg, "file should end in .class.");

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
    FILE* f = svm_get_file_handle(class_file);
    size_t file_length = svm_get_file_size(f);
    unsigned char* data = svm_read_class_file(file_length, f);

    log_trace("Parsing class representation (dumping when complete).");
    svm_display_class_hex(data, file_length);
    svm_class_representation* rep = svm_parse_class_file(file_length, data);
    svm_print_class_overview(rep);

    return EXIT_SUCCESS;
}
