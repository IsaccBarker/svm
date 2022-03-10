#include <svm_class.h>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <limits.h>

#include <svm_log.h>
#include <svm_globals.h>
#include <svm_constant_pool.h>
#include <svm_method_info.h>

svm_class_representation* svm_parse_class_file(size_t file_length, unsigned char* data) {
    uint16_t head = 0;
    svm_class_representation* rep = malloc(file_length);

    if (rep == NULL) {
        log_fatal("Failed to allocate memory to create class rep (%d): %s", file_length, strerror(errno));

        exit(EXIT_FAILURE);
    }

    memset(rep, 0, file_length);

    // Simple science.
    {
        rep->magic = (data[0] << 24) + (data[1] << 16) + (data[2] << 8) + (data[3]);
        head += 4;
        if (rep->magic != 3405691582) {
            log_warn("Class's magic value is not CAFEBABE (3405691582). Possibly corrupted file, or not JVM class file? Continuing...");
        }

        rep->minor_ver = (data[head] << 8) + (data[head+1]);
        head += 2;
        rep->major_ver = (data[head] << 8) + (data[head+1]);
        head += 2;
    }

    // Constant pool
    {
        // https://stackoverflow.com/questions/23674727/jvm-class-format-why-is-constant-pool-count-one-larger-than-it-should-be
        rep->constant_pool_count = (data[head] << 8) + (data[head+1]) - 1;
        head += 2;
        rep->constant_pool = malloc(sizeof(svm_class_cp_info) * rep->constant_pool_count);

        if (rep->constant_pool == NULL) {
            log_fatal("Failed to allocate memory for constant pool (%d): %s", sizeof(svm_class_cp_info) * rep->constant_pool_count, strerror(errno));

            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < rep->constant_pool_count; i++) {
            // uint8_t tag = data[head];
            // char info[CONSTANT_TABLE_BYTE_CAP];

            // printf("%s (%04X)\n", svm_constant_info_as_string(tag), tag);

            for (int i = 0; i < 10; i++) {
                printf("%04X\n", data[head]);

                head++;
            }
        }

        printf("\n");
    }

    // Simple science
    {
        // TODO Access flags (we don't need this for the demo, still nice to have)
        uint16_t access_flags = (data[head] << data[head+1]);
        head += 2;

        // TODO This class (we don't need this for the demo, still nice to have)
        uint16_t this_class = (data[head] << data[head+1]);
        head += 2;

        // TODO Super class (we don't need this for the demo, still nice to have)
        uint16_t super_class = (data[head] << data[head+1]);
        head += 2;

        rep->access_flags = access_flags;
        rep->this_class = this_class;
        rep->super_class = super_class;
    }

    // TODO Interfaces. We don't need them for this demo, hence we don't
    // populate them.
    {
        uint16_t interfaces_count = data[head];
        rep->interfaces_count = interfaces_count;

        head += interfaces_count;
    }

    // Fields
    {
        uint16_t fields_count = data[head];
        rep->fields_count = fields_count;

        head += fields_count * sizeof(svm_class_field_info);
        head += sizeof(uint16_t) * 2;
    }

    // Methods
    /* {
        size_t size_of_method_info = (sizeof(uint16_t) * 4);
        size_t size_of_attribute_info = sizeof(uint8_t*) + sizeof(uint16_t) + sizeof(uint32_t);
        uint16_t methods_count = data[head];
        rep->methods_count = methods_count;
        // We put sizeof() in here because we need to allocate enough for the pointers as well.
        rep->methods = malloc(methods_count * (size_of_method_info + sizeof(attribute_info*) + size_of_attribute_info));
        head += 1;

        for (int i = 0; i < methods_count; i++) {
            uint16_t access_flags = (data[head] << 8) + data[head+1];
            head += 2;
            uint16_t name_index = (data[head] << 8) + data[head+1];
            head += 2;
            uint16_t descriptor_index = (data[head] << 8) + data[head+1];
            head += 2;
            uint16_t attributes_count = (data[head] << 8) + data[head+1];
            head += 2;
            attribute_info* attributes = malloc(attributes_count * sizeof(attribute_info));

            if (attributes == NULL) {
                log_fatal("Failed to allocate memory for attributes: %s\n", strerror(errno));

                exit(EXIT_FAILURE);
            }

            for (int l = 0; l < attributes_count; l++) {
                uint16_t name_index = (data[head] << 8) + data[head+1];
                head += 2;
                uint32_t info_length = (data[head] << 24) + (data[head+1] << 16) + (data[head+2] << 8) + data[head+3];
                head += 4;
                uint8_t* info = malloc(info_length * sizeof(uint8_t));

                if (info == NULL) {
                    log_fatal("Failed to allocate memory for attribute info: %s\n", strerror(errno));

                    exit(EXIT_FAILURE);
                }

                for (uint32_t k = 0; k < info_length; k++) {
                    info[k] = (char) data[head];
                    head += 1;
                }

                attribute_info attrib_info = {
                    .name_index = name_index,
                    .info_length = info_length,
                    .info = info
                };

                attributes[l] = attrib_info;
            }

            method_info info = {
                .access_flags = access_flags,
                .name_index = name_index,
                .descriptor_index = descriptor_index,
                .attributes_count = attributes_count,
                .attributes = attributes
            };

            rep->methods[i] = info;
        }


    }

    // Attributes
    {
        uint16_t attribute_count = (data[head] << 8) + data[head+1];
        rep->attribute_count = attribute_count;

        for (int i = 0; i < attribute_count; i++) {

        }

        // TODO: Our main class (for the demo only) doesn't have any class-wide attributes. Let's ignore this.
    } */

    return rep;
}

void svm_display_class_hex(unsigned char* data, size_t file_length) {
    log_debug("Hexadecimal notation:");
    printf("0:\t");
    for (unsigned int i = 0; i < file_length; i++) {
        printf("%02X", data[i]);

        if (i % 2 == 1) {
            printf(" ");
        }

        if (i % 16 == 15) {
            printf("\n%u: \t", i+1);
        }
    }

    printf("\n");
}

void svm_print_class_overview(svm_class_representation* r) {
    log_debug("Magic                 : %08X", r->magic);
    log_debug("Minor Version         : (0x%04X, %d)", r->minor_ver, r->minor_ver);
    log_debug("Major Version         : (0x%04X, %d)", r->major_ver, r->major_ver);
    log_debug("Constant Pool Count   : %d", r->constant_pool_count);

    for (int i = 0; i < r->constant_pool_count; i++) {
        svm_class_cp_info current_constant = r->constant_pool[i];

        log_trace("\t%d: %s: %s", i+1,
                svm_constant_info_as_string(current_constant.tag), current_constant.info);
    }

    log_debug("Access Flags (s)      : %04X", r->access_flags);
    log_debug("This Class (s)        : %d", r->this_class);
    log_debug("Super Class (s)       : %d", r->super_class);
    log_debug("Interface Count (s)   : %d", r->interfaces_count);

    log_debug("Fields Count (s)      : %d", r->fields_count);

    log_debug("Methods Count         : %d", r->methods_count);

    for (int i = 0; i < r->methods_count; i++) {
        svm_class_method_info current = r->methods[i];

        log_trace("\t%d: Access: %d (%04X), Name Index: %d (%04X), Descriptor Index: %d (%04X), Attributes Count: %d (%04X)", i,
                current.access_flags, current.access_flags, current.name_index, current.name_index,
                current.descriptor_index, current.descriptor_index, current.attributes_count, current.attributes_count);

        for (int l = 0; l < current.attributes_count; l++) {
            svm_class_attribute_info atrib = current.attributes[l];

            log_trace("\t\tAttribute %d -- Name Index: %d (%04X), Info Length: %d (%04X), Info: %s", l,
                    atrib.name_index, atrib.name_index,
                    atrib.info_length, atrib.info_length,
                    atrib.info);
        }
    }

    log_debug("Attribute Count       : %d", r->attribute_count);
}

