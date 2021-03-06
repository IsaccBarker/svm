#include <libsvm/class.h>
#include <libsvm/class_meta.h>
#include <libsvm/log.h>
#include <libsvm/header/magic.h>
#include <libsvm/header/version.h>
#include <libsvm/header/constant_pool.h>
#include <libsvm/header/access_flags.h>
#include <libsvm/header/this_super.h>
#include <libsvm/header/interface.h>
#include <libsvm/header/fields.h>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

svm_class* svm_parse_class(unsigned char* src, size_t length) {
    size_t read_head = 0;
    size_t class_bytes = length + sizeof(svm_class_meta);
    size_t tmp_allocation_size;
    svm_class* class = malloc(class_bytes);

    if (class == NULL) {
        log_fatal("Failed to allocate memory for class file representation (%d bytes): %s", class_bytes, strerror(errno));

        exit(EXIT_FAILURE);
    }

    // Start parsing the class
    read_head += svm_class_get_magic(class, src, read_head);
    read_head += svm_class_get_minor(class, src, read_head);
    read_head += svm_class_get_major(class, src, read_head);
    read_head += svm_class_get_constant_pool_count(class, src, read_head);

    tmp_allocation_size = class->constant_pool_count * sizeof(svm_class_cp_info);
    class->constant_pool = malloc(tmp_allocation_size);

    if (class->constant_pool == NULL) {
        log_fatal("Failed to allocate memory for constant pool (%d): %s", tmp_allocation_size, strerror(errno));

        exit(EXIT_FAILURE);
    }

    read_head += svm_class_get_constant_pool(class, src, read_head);
    read_head += svm_class_get_access_flags(class, src, read_head);
    read_head += svm_class_get_this_super(class, src, read_head);
    read_head += svm_class_get_interfaces_count(class, src, read_head);

    tmp_allocation_size = class->interfaces_count * sizeof(uint16_t);
    class->interfaces = malloc(tmp_allocation_size);

    if (class->interfaces == NULL) {
        log_fatal("Failed to allocate memory for interfaces (%d): %s", tmp_allocation_size, strerror(errno));

        exit(EXIT_FAILURE);
    }

    read_head += svm_class_get_interfaces(class, src, read_head);
    read_head += svm_class_get_fields_count(class, src, read_head);

    svm_verify_version_validity(class);
    svm_account_for_preview_features(class);

    return class;
}

void svm_display_class_hex(unsigned char* src, size_t length) {
    log_debug("Hexadecimal notation:");
    printf("0:\t");

    for (unsigned int i = 0; i < length; i++) {
        printf("%02X", src[i]);

        if (i % 2 == 1) {
            printf(" ");
        }

        if (i % 16 == 15) {
            printf("\n%u: \t", i+1);
        }
    }

    printf("\n");
}

void svm_dump_class(svm_class* class) {
    assert(class != NULL);

    // We use 72 here because this is the max
    // possible number of characters that
    // svm_class_get_access_flags_as_string
    // will spit out, plus a null terminator.
    char access_flags_str_buf[72];

    log_debug("Meta: ");
    log_debug("\tPreview Features : %s",
            class->meta.feature_preview == 1 ? "yes" : "no");
    log_debug("Magic : 0x%08X", class->magic);
    log_debug("Major Version : %d", class->major_version);
    log_debug("Minor Version : %d", class->minor_version);
    log_debug("Human Version : %s", svm_get_human_java_version(class));
    log_debug("Constant Pool Count : %d", class->constant_pool_count);
    log_trace("Constant Pool Entries :");

    for (int i = 0; i < class->constant_pool_count-1; i++) {
        uint8_t tag = class->constant_pool[i].tag;

        log_trace("%d. %s", i+1, svm_class_constant_tag_as_string(tag));
        svm_class_print_constant_entry(tag, class->constant_pool[i].further, class->constant_pool);
    }

    // We don't put a space between %s and %04X because
    // svm_class_get_access_flags_as_string leaves a space
    // at the end for the sake of performance.
    //
    // Not that it makes much difference.
    log_debug("Access Flags : %s(0x%04X)",
            svm_class_get_access_flags_as_string(class->access_flags, access_flags_str_buf),
            class->access_flags);
    log_debug("This Class : %d", class->this_class);
    log_debug("Super Class : %d", class->super_class);
    log_debug("Interfaces Count: %d", class->interfaces_count);
    log_trace("Interfaces (if any) :");

    for (int i = 0; i < class->interfaces_count; i++) {
        log_trace("%d. %d", i, class->interfaces[i]);
    }

    log_debug("Fields Count: %d", class->fields_count);
}

