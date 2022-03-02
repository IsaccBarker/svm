#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <assert.h>

#include <svm_const.h>
#include <svm_globals.h>
#include <svm_file.h>
#include <svm_class.h>

int main(int argc, char *argv[]) {
    int c;
    while (1) {
        int option_index = 0;
        static struct option long_options[] = {
            {"verbose", no_argument, &verbose_flag, 1},
            {"class", required_argument, 0, 'c'},
            {0, 0, 0, 0}
        };

        c = getopt_long (argc, argv, "vc:",
                    long_options, &option_index);

        if (c == -1) { break; }

        switch (c) {
            case 0:
                if (long_options[option_index].flag != 0)
                    break;

                printf("option %s", long_options[option_index].name);

                if (optarg)
                    printf(" with arg %s", optarg);

                puts("\n");

                break;

            case 'v':
                verbose_flag = 1;

                break;

            case 'c':
                class_file = optarg;

                break;

            case '?':
                // Getopt already printed a message.

                break;

            default:
                abort();
        }
    }

    /* Print any remaining command line arguments (not options). */
  if (optind < argc) {
        fprintf(stderr, "%s: unknown elements (svm does not use subcommands): ", SVM_NAME);
        while (optind < argc)
            fprintf(stderr, "\n\t%s", argv[optind++]);

        fprintf(stderr, "\n%s: this is not a fatal error, these excess elements will be ignored.\n", SVM_NAME);
    }

    if (class_file == NULL) {
        fprintf(stderr, "%s: no class file was specified.", SVM_NAME);

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
