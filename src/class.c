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
#include <svm_constant_pool.h>
#include <svm_method_info.h>

void svm_start_virtual_machine(char* class_file) {
    log_trace("Reading class file.");
    FILE* f = svm_get_file_handle(class_file);
    size_t file_length = svm_get_file_size(f);
    unsigned char* data = svm_read_class_file(file_length, f);
    uint16_t head = 0;
    svm_class_representation* rep = malloc(file_length);

    display_class_hex(data, file_length);

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

        head = 8;
    }

    // Constant pool
    {
        size_t constant_offset = 0;

        // https://stackoverflow.com/questions/23674727/jvm-class-format-why-is-constant-pool-count-one-larger-than-it-should-be
        rep->constant_pool_count = (data[8] << 8) + (data[9]) - 1;
        rep->constant_pool = malloc(sizeof(cp_info) * rep->constant_pool_count);

        if (rep->constant_pool == NULL) {
            log_fatal("Failed to allocate memory for constant pool (%d): %s", sizeof(cp_info) * rep->constant_pool_count, strerror(errno));

            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < rep->constant_pool_count; i++) {
            uint8_t tag = data[10+constant_offset];
            uint16_t first = data[11+constant_offset] << 8;
            size_t info_length;
            uint8_t* info;

            first += data[12+constant_offset];
            first += 1;

            info_length = svm_constant_info_length(tag, first);
            constant_offset += info_length;
            info = malloc(info_length * sizeof(uint8_t));

            for (size_t l = 0; l < info_length; l++) {
                if (l == info_length) {
                    info[l] = data[11+l+constant_offset];
                }

                info[l] = data[11+l+constant_offset] << ((info_length-l)*8);
            }

            cp_info cp_entry = {
                .tag = tag,
                .info_length = info_length,
                .info = info
            };

            rep->constant_pool[i] = cp_entry;
        }

        head += constant_offset;
    }

    // I think this is in the standard?
    // Either way, not gonna mess with it.
    head += 3;

    // Simple science
    {
        // TODO Access flags
        // 137 138
        uint16_t access_flags = (data[head] << data[head+1]);

        // TODO This class
        head += 2;

        // TODO Super class
        head += 2;

        rep->access_flags = access_flags;
    }

    head += 1;

    // TODO Interfaces
    {
        uint16_t interfaces_count = data[head];
        rep->interfaces_count = interfaces_count;

        head += interfaces_count;
    }

    // Fields
    {
        uint16_t fields_count = data[head];
        rep->fields_count = fields_count;

        head += fields_count * sizeof(field_info);
        head += sizeof(uint16_t) * 2;
    }

    head += 1;

    // Methods
    {
        uint16_t methods_count = data[head];
        rep->methods_count = methods_count;
        rep->methods = malloc(methods_count * sizeof(method_info));

        if (rep->methods == NULL) {
            log_fatal("Failed to allocate memory for method table: ", strerror(errno));

            exit(EXIT_FAILURE);
        }

        for (size_t i = 0; i < methods_count; i++) {
            uint16_t access_flags = (data[head+1] << 8) + data[head+2];
            head += 2;
            uint16_t name_index = (data[head+1] << 8) + data[head+2];
            head += 2;
            uint16_t descriptor_index = (data[head+1] << 8) + data[head+2];
            head += 2;
            uint16_t attributes_count = (data[head+1] << 8) + data[head+2];
            head += 2;

            attribute_info* attributes = malloc(attributes_count * sizeof(attribute_info));

            for (int l = 0; l < attributes_count; l++) {
                uint16_t name_index = (data[head+1] << 8) + data[head+2];
                head += 2;
                uint32_t info_length = (data[head+1] << 8) + data[head+2];
                head += 4;
                uint8_t* info = malloc(info_length * sizeof(uint8_t));

                for (int p = 0; p < info_length; p++) {
                    info[p] = data[head];
                    head += 1;
                }

                if (info == NULL) {
                    log_fatal("Failed to allocate memory for attribute info: %s", strerror(errno));

                    exit(EXIT_FAILURE);
                }

                attribute_info atrib = {
                    .name_index = name_index,
                    .info_length = info_length,
                    .info = info
                };

                attributes[l] = atrib;
            }

            attribute_info atrib_info;

            method_info info = {
                .access_flags = access_flags,
                .name_index = name_index,
                .descriptor_index = descriptor_index,
                .attributes_count = attributes_count,
                .attributes = attributes,
            };

            rep->methods[i] = info;
        }
    }

    // Attributes
    {

    }

    svm_print_class_overview(rep);
}

void display_class_hex(unsigned char* data, size_t file_length) {
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
        log_trace("\t%d: %s", i,
                svm_constant_info_as_string(r->constant_pool[i].tag, r->constant_pool[i].info[0]));
    }

    log_debug("Access Flags (s)      : %04X", r->access_flags);
    log_debug("This Class (s)        : %d", r->this_class);
    log_debug("Super Class (s)       : %d", r->super_class);
    log_debug("Interface Count (s)   : %d", r->interfaces_count);

    log_debug("Fields Count (s)      : %d", r->fields_count);

    log_debug("Methods Count         : %d", r->methods_count);

    for (int i = 0; i < r->methods_count; i++) {
        method_info current = r->methods[i];

        log_trace("\t%d: Access: %d (%04X), Name Index: %d (%04X), Descriptor Index: %d (%04X), Attributes Count: %d (%04X)", i,
                current.access_flags, current.access_flags, current.name_index, current.name_index,
                current.descriptor_index, current.descriptor_index, current.attributes_count, current.attributes_count);

        for (int l = 0; l < current.attributes_count; l++) {
            attribute_info atrib = current.attributes[l];

            log_trace("\t\tAttribute %d -- Name Index: %d (%04X), Info Length: %d (%04X), Info: %s", l,
                    atrib.name_index, atrib.name_index,
                    atrib.info_length, atrib.info_length,
                    atrib.info);
        }
    }

    log_debug("Attribute Count       : %d", r->attribute_count);
}

