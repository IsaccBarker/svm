#include <svm_constant_pool.h>

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <limits.h>

#include <svm_log.h>

size_t svm_class_tag_constant_to_size(uint8_t tag) {
    switch (tag) {
        case SVM_CONSTANT_TAG_UTF8:
            // The UTF8 constant type does not have a
            // fixed size.
            return CHAR_MAX;
        case SVM_CONSTANT_TAG_INTEGER:
            return SVM_CONSTANT_TAG_SIZE_INTEGER;
        case SVM_CONSTANT_TAG_FLOAT:
            return SVM_CONSTANT_TAG_SIZE_FLOAT;
        case SVM_CONSTANT_TAG_LONG:
            return SVM_CONSTANT_TAG_SIZE_LONG;
        case SVM_CONSTANT_TAG_DOUBLE:
            return SVM_CONSTANT_TAG_SIZE_DOUBLE;
        case SVM_CONSTANT_TAG_CLASS:
            return SVM_CONSTANT_TAG_SIZE_CLASS;
        case SVM_CONSTANT_TAG_STRING:
            return SVM_CONSTANT_TAG_SIZE_STRING;
        case SVM_CONSTANT_TAG_FIELD_REF:
            return SVM_CONSTANT_TAG_SIZE_FIELD_REF;
        case SVM_CONSTANT_TAG_METHOD_REF:
            return SVM_CONSTANT_TAG_SIZE_METHOD_REF;
        case SVM_CONSTANT_TAG_INTERFACE_METHOD_REF:
            return SVM_CONSTANT_TAG_SIZE_INTERFACE_METHOD_REF;
        case SVM_CONSTANT_TAG_NAME_AND_TYPE:
            return SVM_CONSTANT_TAG_SIZE_NAME_AND_TYPE;
        case SVM_CONSTANT_TAG_METHOD_HANDLE:
            return SVM_CONSTANT_TAG_SIZE_METHOD_HANDLE;
        case SVM_CONSTANT_TAG_METHOD_TYPE:
            return SVM_CONSTANT_TAG_SIZE_METHOD_TYPE;
        case SVM_CONSTANT_TAG_INVOKE_DYNAMIC:
            return SVM_CONSTANT_TAG_SIZE_INVOKE_DYNAMIC;
        default:
            // log_fatal("Unknown constant type when getting tag info length (%d, %04X).", tag, tag);
            log_fatal("Unknown constant pool tag (%d, 0x%02X).", tag, tag);


            exit(EXIT_FAILURE);
    }
}

char* svm_constant_tag_as_string(uint8_t tag) {
    switch (tag) {
        case SVM_CONSTANT_TAG_CLASS:
            return "Class";
        case SVM_CONSTANT_TAG_FIELD_REF:
            return "FieldRef";
        case SVM_CONSTANT_TAG_METHOD_REF:
            return "MethodRef";
        case SVM_CONSTANT_TAG_INTERFACE_METHOD_REF:
            return "InterfaceMethodRef";
        case SVM_CONSTANT_TAG_STRING:
            return "String";
        case SVM_CONSTANT_TAG_INTEGER:
            return "Integer";
        case SVM_CONSTANT_TAG_FLOAT:
            return "Float";
        case SVM_CONSTANT_TAG_LONG:
            return "Long";
        case SVM_CONSTANT_TAG_DOUBLE:
            return "Double";
        case SVM_CONSTANT_TAG_NAME_AND_TYPE:
            return "NameAndType";
        case SVM_CONSTANT_TAG_UTF8:
            return "UTF8";
        case SVM_CONSTANT_TAG_METHOD_HANDLE:
            return "MethodHandle";
        case SVM_CONSTANT_TAG_METHOD_TYPE:
            return "MethodType";
        case SVM_CONSTANT_TAG_INVOKE_DYNAMIC:
            return "InvokeDynamic";
        default:
            log_fatal("Unknown constant pool tag (%d, 0x%02X).", tag, tag);

            exit(EXIT_FAILURE);
    }
}

uint16_t svm_class_get_constant_pool_count(svm_class* class, unsigned char* src, size_t offset) {
    class->constant_pool_count = (src[offset] << 8) + src[offset+1];

    return 2;
}

uint16_t svm_class_get_constant_pool(svm_class* class, unsigned char* src, size_t offset) {
    for (size_t constant_index = 0; constant_index < class->constant_pool_count; constant_index++) {
        // TODO: FUTURE ME
        // what appears to not work is that svm_class_get_next_constant_entry is returning the
        // wrong offset modifyer. This happens in the "main" logic, and not the UTF8 logic.
        // FYI :)

        printf("%zu\n", offset);
        offset += svm_class_get_next_constant_entry(&class->constant_pool[constant_index], src, offset);
        printf("%zu\n", offset);
    }

    return 0;
}

size_t svm_class_get_next_constant_entry(svm_class_cp_info* info, unsigned char* src, size_t offset) {
    uint8_t tag = src[offset];
    size_t info_size = svm_class_tag_constant_to_size(tag);

    offset += 1;

    // Check if we can just copy the bytes in
    // due to a fixed size.
    if (info_size != CHAR_MAX) {
        // Yes we can!

        uint8_t* info_bytes = malloc(info_size * sizeof(uint8_t));

        // Loop over the bytes, and do some fancy
        // bit shifting to populate the info struct
        // (whatever it might be).
        for (size_t i = 0; i < info_size; i++) {
            info_bytes[i] += (src[offset] << i*3);

            offset += 1;
        }

        info->tag = tag;
        info->further = info_bytes;
    } else {
        // No, we can't. Chances are this is a UTF8 string
        // Thus, we check for a UTF8 string, and spin off
        // that parsing function if we finc one.
        if (tag == SVM_CONSTANT_TAG_UTF8) {
            offset += svm_class_get_next_constant_entry_utf8(info, src, offset);
        } else {
            log_fatal("Unknown non-fixed size constant table tag.");

            exit(EXIT_FAILURE);
        }

        assert(info->further != NULL);
    }

    // Add 1 to the offset so we read the byte after
    // (said byte is the tag).
    offset += 1;

    return offset;
}

size_t svm_class_get_next_constant_entry_utf8(svm_class_cp_info* info, unsigned char* src, size_t offset) {
    uint16_t length = (src[offset] << 8) + src[offset+1];
    char* str = malloc(length * sizeof(uint8_t));

    offset += 2;

    // Loop over the characters until we get the entire string
    // loaded in.
    for (int i = 0; i < length; i++) {
        str[i] = src[offset];

        offset += 1;
    }

    info->further = info;

    return length;
}

