#include <svm_constant_pool.h>

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

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

void scm_class_create_fixed_constant_entry(svm_class_cp_info* info, unsigned char* src, size_t offset) {
    switch (tag) {
        case SVM_CONSTANT_TAG_CLASS: {
            svm_class_class* further = malloc(SVM_CONSTANT_TAG_SIZE_CLASS);
            break;
        }
        case SVM_CONSTANT_TAG_FIELD_REF: {
            svm_class_field_ref* further = malloc(SVM_CONSTANT_TAG_SIZE_FIELD_REF);
            break;
        }
        case SVM_CONSTANT_TAG_METHOD_REF: {
            svm_class_field_ref* further = malloc(SVM_CONSTANT_TAG_SIZE_METHOD_REF);
            break;
        }
        case SVM_CONSTANT_TAG_INTERFACE_METHOD_REF: {
            svm_class_field_ref* further = malloc(SVM_CONSTANT_TAG_SIZE_INTERFACE_METHOD_REF);
            break;
        }
        case SVM_CONSTANT_TAG_STRING: {
            svm_class_string* further = malloc(SVM_CONSTANT_TAG_SIZE_INTERFACE_METHOD_REF);
            break;
        }
        case SVM_CONSTANT_TAG_INTEGER: {
            break;
        }
        case SVM_CONSTANT_TAG_FLOAT: {
            break;
        }
        case SVM_CONSTANT_TAG_LONG: {
            break;
        }
        case SVM_CONSTANT_TAG_DOUBLE: {
            break;
        }
        case SVM_CONSTANT_TAG_NAME_AND_TYPE: {
            break;
        }
        case SVM_CONSTANT_TAG_UTF8: {
            break;
        }
        case SVM_CONSTANT_TAG_METHOD_HANDLE: {
            break;
        }
        case SVM_CONSTANT_TAG_METHOD_TYPE: {
            break;
        }
        case SVM_CONSTANT_TAG_INVOKE_DYNAMIC: {
            break;
        }
        default:
            log_fatal("Unknown constant pool tag (%d, 0x%02X).", tag, tag);

            exit(EXIT_FAILURE);
    }

}

void svm_class_print_constant_entry(svm_class_cp_info* info) {
    uint8_t tag = info->tag;

    switch (tag) {
        case SVM_CONSTANT_TAG_CLASS: {
            svm_class_class* typed_info = info->further;
            log_trace("-- Name index : %04X (%d)", typed_info->name_index, typed_info->name_index);

            break;
        }
        case SVM_CONSTANT_TAG_FIELD_REF: {
            svm_class_field_ref* typed_info = info->further;

            break;
        }
        case SVM_CONSTANT_TAG_METHOD_REF: {
            svm_class_method_ref* typed_info = info->further;

            break;
        }
        case SVM_CONSTANT_TAG_INTERFACE_METHOD_REF: {
            svm_class_interface_method_ref* typed_info = info->further;

            break;
        }
        case SVM_CONSTANT_TAG_STRING: {
            svm_class_string* typed_info = info->further;

            break;
        }
        case SVM_CONSTANT_TAG_INTEGER: {
            svm_class_int* typed_info = info->further;

            break;
        }
        case SVM_CONSTANT_TAG_FLOAT: {
            svm_class_float* typed_info = info->further;

            break;
        }
        case SVM_CONSTANT_TAG_LONG: {
            // Fuck. You. Mr. Long.
            svm_class_long* typed_info = info->further;

            break;
        }
        case SVM_CONSTANT_TAG_DOUBLE: {
            svm_class_double* typed_info = info->further;

            break;
        }
        case SVM_CONSTANT_TAG_NAME_AND_TYPE: {
            svm_class_name_and_type* typed_info = info->further;
            break;
        }
        case SVM_CONSTANT_TAG_UTF8: {
            svm_class_utf8* typed_info = info->further;

            log_trace("-- String : %s", typed_info->bytes);

            break;
        }
        case SVM_CONSTANT_TAG_METHOD_HANDLE: {
            svm_class_method_handle* typed_info = info->further;

            break;
        }
        case SVM_CONSTANT_TAG_METHOD_TYPE: {
            svm_class_method_type* typed_info = info->further;

            break;
        }
        case SVM_CONSTANT_TAG_INVOKE_DYNAMIC: {
            svm_class_invoke_dynamic* typed_info = info->further;

            break;
        }
        default: {
            log_fatal("Unknown constant pool tag (%d, 0x%02X).", tag, tag);

            exit(EXIT_FAILURE);
        }
    }
}

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

        if (info_bytes == NULL) {
            log_fatal("Failed to allocate memory for fixed size constant table entry (%d): %s",
                    strerror(errno), info_bytes_length);

            exit(EXIT_FAILURE);
        }

        // Loop over the bytes, and do some fancy
        // bit shifting to populate the info struct
        // (whatever it might be).
        svm_class_

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

