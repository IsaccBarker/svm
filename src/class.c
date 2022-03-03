#include <svm_class.h>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <limits.h>

#include <svm_log.h>
#include <svm_bit.h>
#include <svm_class_file.h>

void svm_start_virtual_machine(char* class_file) {
    log_trace("Reading class file.");
    FILE* f = svm_get_file_handle(class_file);
    size_t file_length = svm_get_file_size(f);
    unsigned char* data = svm_read_class_file(file_length, f);
    svm_class_representation* representation = malloc(file_length);

    if (representation == NULL) {
        log_fatal("Failed to allocate memory to create class representation (%d): %s", file_length, strerror(errno));

        exit(EXIT_FAILURE);
    }

    // Arrays in C are stored continuously.
    representation = (svm_class_representation*) &data;

    printf("EUIWUGNGWE: %d\n", representation->magic);

    display_class_hex(data, file_length);
    svm_print_class_overview(representation);
}

void display_class_hex(unsigned char* data, size_t file_length) {
    printf("\t");
    for (unsigned int i = 0; i < file_length; i++) {
        printf("%-4X ", data[i]);

        if (i % 16 == 15) {
            printf("\n\t");
        }
    }

    printf("\n");
}

void svm_print_class_overview(svm_class_representation* r) {
    printf(
            "Magic                 : %d\n"
            "Minor Version         : %d\n"
            "Major Version         : %d\n"
            "Constant Pool Count   : %d\n"
            "Access Flags          : %d\n"
            "This Class            : %d\n"
            "Super Class           : %d\n"
            "Interface Count       : %d\n"
            "Fields Count          : %d\n"
            "Methods Count         : %d\n"
            "Attribute Count       : %d\n",
            r->magic, r->minor_ver, r->major_ver, r->constant_pool_count,
            r->access_flags, r->this_class, r->super_class, r->interfaces_count,
            r->fields_count, r->methods_count, r-> attribute_count
            );
}

