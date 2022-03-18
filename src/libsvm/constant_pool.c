#include <svm_constant_pool.h>

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

#include <svm_log.h>

uint16_t svm_class_get_constant_pool_count(svm_class* class, unsigned char* src, size_t offset) {
    class->constant_pool_count = (src[offset] << 8) + src[offset+1];

    return 2;
}

uint16_t svm_class_get_constant_pool(svm_class* class, unsigned char* src, size_t offset) {
    for (size_t constant_index = 0; constant_index < class->constant_pool_count-1; constant_index++) {
        offset += svm_class_get_next_constant_entry(&class->constant_pool[constant_index], src, offset);
    }

    return 0;
}

size_t svm_class_get_next_constant_entry(svm_class_cp_info* info, unsigned char* src, size_t offset) {
    uint8_t tag = src[offset];
    size_t info_size = svm_class_tag_constant_to_size(tag);
    size_t track_offset = 0;

    track_offset += 1;
    offset += 1;

    // Check if we can just copy the bytes in
    // due to a fixed size.
    if (info_size != CHAR_MAX) {
        // Yes we can!
        size_t info_bytes_length = info_size * sizeof(uint8_t);
        void* further = malloc(info_bytes_length);

        if (further == NULL) {
            log_fatal("Failed to allocate memory for fixed size constant table entry (%d): %s",
                    strerror(errno), info_bytes_length);

            exit(EXIT_FAILURE);
        }

        // Because all the tags indicate data with a different
        // scheme, we have to parse through the info provided.
        // And no, we cannot just cast from the source array
        // into the struct, I tried that :D
        svm_class_create_fixed_constant_entry(further, tag, src, offset);

        track_offset += info_size;

        info->tag = tag;
        info->further = further;
    } else {
        // No, we can't. Chances are this is a UTF8 string
        // Thus, we check for a UTF8 string, and spin off
        // that parsing function if we finc one.
        // TODO: Use track offset
        if (tag == SVM_CONSTANT_TAG_UTF8) {
            track_offset += svm_class_get_next_constant_entry_utf8(info, src, offset);
        } else {
            log_fatal("Unknown non-fixed size constant table tag.");

            exit(EXIT_FAILURE);
        }

        assert(info->further != NULL);
    }

    // Add 1 to the offset so we read the byte after
    // (said byte is the tag).
    // track_offset += 1;

    return track_offset;
}

size_t svm_class_get_next_constant_entry_utf8(svm_class_cp_info* info, unsigned char* src, size_t offset) {
    uint16_t length = (src[offset] << 8) + src[offset+1];
    size_t track_offset = length;
    uint8_t* str = malloc(length * sizeof(uint8_t) + 1);
    svm_class_utf8* typed_info = malloc(SVM_CONSTANT_TAG_SIZE_UTF8);

    if (typed_info == NULL) {
        log_fatal("Failed to allocatae memory for UTF8 typed info (%d): %s",
                SVM_CONSTANT_TAG_SIZE_UTF8, strerror(errno));
    }

    offset += 2;

    // Loop over the characters until we get the entire string
    // loaded in.
    for (int i = 0; i < length; i++) {
        str[i] = src[offset];

        offset += 1;
    }

    str[length] = '\0';

    typed_info->bytes = str;

    info->further = typed_info;
    info->tag = SVM_CONSTANT_TAG_UTF8;

    // TODO: What the actual fuck does this do.
    track_offset += 2;

    return track_offset;
}

