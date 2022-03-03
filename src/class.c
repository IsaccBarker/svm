#include <svm_class.h>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <limits.h>

#include <svm_log.h>
#include <svm_bit.h>
#include <svm_globals.h>
#include <svm_class_file.h>

void svm_start_virtual_machine(char* class_file) {
    log_trace("Reading class file.");
    FILE* f = svm_get_file_handle(class_file);
    size_t file_length = svm_get_file_size(f);
    unsigned char* data = svm_read_class_file(file_length, f);
    svm_class_representation* rep = malloc(file_length);

    if (rep == NULL) {
        log_fatal("Failed to allocate memory to create class rep (%d): %s", file_length, strerror(errno));

        exit(EXIT_FAILURE);
    }

    memset(rep, 0, file_length);

    // Simple science.
    {
        rep->magic = (data[0] << 24) + (data[1] << 16) + (data[2] << 8) + (data[3]);
        if (rep->magic != 3405691582) {
            log_warn("Class's magic value is not CAFEBABE (3405691582). Possibly corrupted file? Continuing...");
        }

        rep->minor_ver = (data[4] << 8) + (data[5]);
        rep->major_ver = (data[6] << 8) + (data[7]);
    }

    // Constant pool
    {
        // https://stackoverflow.com/questions/23674727/jvm-class-format-why-is-constant-pool-count-one-larger-than-it-should-be
        rep->constant_pool_count = (data[8] << 8) + (data[9]) - 1;

        for (int i = 0; i < rep->constant_pool_count; i++) {
            unsigned char type = data[10+i];

            printf("%zu\n", svm_info_length(type));
        }
    }

    display_class_hex(data, file_length);
    svm_print_class_overview(rep);
}

void display_class_hex(unsigned char* data, size_t file_length) {
    log_debug("Hexadecimal notation:");
    printf("\t");
    for (unsigned int i = 0; i < file_length; i++) {
        printf("%02X", data[i]);

        if (i % 2 == 1) {
            printf(" ");
        }

        if (i % 16 == 15) {
            printf("\n\t");
        }
    }

    printf("\n");
}

void svm_print_class_overview(svm_class_representation* r) {
    log_debug(
            "\n"
            "\tMagic                 : %08X\n"
            "\tMinor Version         : " BYTE_TO_BINARY_PATTERN "" BYTE_TO_BINARY_PATTERN " (0x%04X, %d)\n"
            "\tMajor Version         : " BYTE_TO_BINARY_PATTERN "" BYTE_TO_BINARY_PATTERN " (0x%04X, %d)\n"
            "\tConstant Pool Count   : %d\n"
            "\tINACCURATE:\n"
            "\tAccess Flags          : %04X\n"
            "\tThis Class            : %d\n"
            "\tSuper Class           : %d\n"
            "\tInterface Count       : %d\n"
            "\tFields Count          : %d\n"
            "\tMethods Count         : %d\n"
            "\tAttribute Count       : %d\n",
            r->magic,
            BYTE_TO_BINARY(r->minor_ver>>8), BYTE_TO_BINARY(r->minor_ver), r->minor_ver, r->minor_ver,
            BYTE_TO_BINARY(r->major_ver>>8), BYTE_TO_BINARY(r->major_ver), r->major_ver, r->major_ver,
            r->constant_pool_count,
            // INACCURATE
            r->access_flags, r->this_class, r->super_class,
            r->interfaces_count, r->fields_count, r->methods_count, r-> attribute_count
            );
}

