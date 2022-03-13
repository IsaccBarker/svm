#include <svm_class.h>
#include <svm_class_meta.h>
#include <svm_log.h>
#include <svm_magic.h>
#include <svm_version.h>
#include <svm_constant_pool.h>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

svm_class* svm_parse_class(unsigned char* src, size_t length) {
    size_t read_head = 0;
    size_t class_bytes = length + sizeof(svm_class_meta);
    svm_class* class = malloc(class_bytes);

    if (class == NULL) {
        log_fatal("Failed to allocate memory for class file representation (%d bytes).", class_bytes);
    }

    // Start parsing the class
    read_head += svm_class_get_magic(class, src, read_head);
    read_head += svm_class_get_minor(class, src, read_head);
    read_head += svm_class_get_major(class, src, read_head);
    read_head += svm_class_get_constant_pool_count(class, src, read_head);
    read_head += svm_class_get_constant_pool(class, src, read_head);

    svm_verify_version_validity(class);
    svm_account_for_preview_features(class);

    return class;
}

void svm_dump_class(svm_class* class) {
    assert(class != NULL);

    log_debug("Meta: ");
    log_debug("\tPreview Features: %d", class->meta.feature_preview);
    log_debug("Magic               : 0x%08X", class->magic);
    log_debug("Minor Version       : %d (0x%04X)", class->minor_version, class->minor_version);
    log_debug("Major Version       : %d (0x%04X)", class->major_version, class->major_version);
    log_debug("Human Version       : %s", svm_get_human_java_version(class));
    log_debug("Constant Pool Count : %d (0x%04X)", class->constant_pool_count);
}

