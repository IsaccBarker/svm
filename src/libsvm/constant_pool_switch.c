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
        case SVM_CONSTANT_TAG_CLASS_MODULE:
            return "ClassModule";
        case SVM_CONSTANT_TAG_CLASS_PACKAGE:
            return "ClassPackage";
        default:
            log_fatal("Unknown constant pool tag (%d, 0x%02X).", tag, tag);

            exit(EXIT_FAILURE);
    }
}

// TODO: VERY MUCH optimize for DRY.
uint16_t svm_class_create_fixed_constant_entry(void* further, uint8_t tag, unsigned char* src, size_t offset) {
    switch (tag) {
        case SVM_CONSTANT_TAG_CLASS:
            ((svm_class_class*)further)->name_index =
                (src[offset] << 8) + src[offset+1];
            return 2;
        case SVM_CONSTANT_TAG_FIELD_REF:
            ((svm_class_field_ref*)further)->class_index =
                (src[offset] << 8) + src[offset+1];
            ((svm_class_field_ref*)further)->name_and_type_index =
                (src[offset+2] << 8) + src[offset+3];
            return 4;
        case SVM_CONSTANT_TAG_METHOD_REF:
            ((svm_class_field_ref*)further)->class_index =
                (src[offset] << 8) + src[offset+1];
            ((svm_class_field_ref*)further)->name_and_type_index =
                (src[offset+2] << 8) + src[offset+3];
            return 4;
        case SVM_CONSTANT_TAG_INTERFACE_METHOD_REF:
            ((svm_class_field_ref*)further)->class_index =
                (src[offset] << 8) + src[offset+1];
            ((svm_class_field_ref*)further)->name_and_type_index =
                (src[offset+2] << 8) + src[offset+3];
            return 4;
        case SVM_CONSTANT_TAG_STRING:
            ((svm_class_string*)further)->string_index =
                (src[offset] << 8) + src[offset+1];
            return 2;
        case SVM_CONSTANT_TAG_INTEGER:
            ((svm_class_int*)further)->bytes =
                (src[offset] << 24) + (src[offset+1] << 16) +
                (src[offset+2] << 8) + src[offset+3];
            return 4;
        case SVM_CONSTANT_TAG_FLOAT:
            ((svm_class_float*)further)->bytes =
                (src[offset] << 24) + (src[offset+1] << 16) +
                (src[offset+2] << 8) + src[offset+3];
            return 4;
        case SVM_CONSTANT_TAG_LONG:
            ((svm_class_long*)further)->low =
                (src[offset] << 24) + (src[offset+1] << 16) +
                (src[offset+2] << 8) + src[offset+3];

            ((svm_class_long*)further)->high =
                (src[offset+4] << 24) + (src[offset+5] << 16) +
                (src[offset+6] << 8) + src[offset+7];
            return 8;
        case SVM_CONSTANT_TAG_DOUBLE:
            ((svm_class_double*)further)->low =
                (src[offset] << 24) + (src[offset+1] << 16) +
                (src[offset+2] << 8) + src[offset+3];

            ((svm_class_double*)further)->high =
                (src[offset+4] << 24) + (src[offset+5] << 16) +
                (src[offset+6] << 8) + src[offset+7];
            return 8;
        case SVM_CONSTANT_TAG_NAME_AND_TYPE:
            ((svm_class_name_and_type*)further)->name_index =
                (src[offset] << 8) + src[offset+1];
            ((svm_class_name_and_type*)further)->descriptor_index =
                (src[offset+2] << 8) + src[offset+3];
            return 4;
        case SVM_CONSTANT_TAG_METHOD_HANDLE:
            ((svm_class_method_handle*)further)->reference_kind =
                src[offset];
            ((svm_class_method_handle*)further)->reference_index =
                (src[offset+1] << 8) + src[offset+2];
            return 3;
        case SVM_CONSTANT_TAG_METHOD_TYPE:
            ((svm_class_method_type*)further)->descriptor_index =
                (src[offset] << 8) + src[offset+1];
            return 2;
        case SVM_CONSTANT_TAG_INVOKE_DYNAMIC:
            ((svm_class_invoke_dynamic*)further)->bootstrap_method_attr_index =
                (src[offset] << 8) + src[offset+1];
            ((svm_class_invoke_dynamic*)further)->name_and_type_index =
                (src[offset+2] << 8) + src[offset+3];
            return 4;
        case SVM_CONSTANT_TAG_CLASS_MODULE:
            ((svm_class_class_module*)further)->name_index =
                (src[offset] << 8) + src[offset+1];
            return 2;
        case SVM_CONSTANT_TAG_CLASS_PACKAGE:
            ((svm_class_class_package*)further)->name_index =
                (src[offset] << 8) + src[offset+1];
            return 2;
        default:
            log_fatal("Unknown constant fixed-size pool tag (%d, 0x%02X).", tag, tag);

            exit(EXIT_FAILURE);
    }

    log_fatal("Uncaught fixed-size constant.");
    exit(EXIT_FAILURE);
}

void svm_class_print_constant_entry(uint16_t tag, void* further, svm_class_cp_info* pool) {
    switch (tag) {
        case SVM_CONSTANT_TAG_CLASS: {
            svm_class_class* typed_info = further;

            log_trace("-- Name index : %04X (%d)",
                    typed_info->name_index, typed_info->name_index);

            break;
        }
        case SVM_CONSTANT_TAG_FIELD_REF: {
            svm_class_field_ref* typed_info = further;

            log_trace("-- Class Index : %04X (%d)",
                    typed_info->class_index, typed_info->class_index);
            log_trace("-- Name & Type Index : %04X (%d)",
                    typed_info->name_and_type_index, typed_info->name_and_type_index);

            break;
        }
        case SVM_CONSTANT_TAG_METHOD_REF: {
            svm_class_method_ref* typed_info = further;

            log_trace("-- Class Index : %04X (%d)",
                    typed_info->class_index, typed_info->class_index);
            log_trace("-- Name & Type Index : %04X (%d)",
                    typed_info->name_and_type_index, typed_info->name_and_type_index);

            break;
        }
        case SVM_CONSTANT_TAG_INTERFACE_METHOD_REF: {
            svm_class_interface_method_ref* typed_info = further;

            log_trace("-- Class Index : %04X (%d)",
                    typed_info->class_index, typed_info->class_index);
            log_trace("-- Name & Type Index : %04X (%d)",
                    typed_info->name_and_type_index, typed_info->name_and_type_index);

            break;
        }
        case SVM_CONSTANT_TAG_STRING: {
            svm_class_string* typed_info = further;

            log_trace("-- UTF8 Index : %04X (%d)",
                    typed_info->string_index, typed_info->string_index);

            break;
        }
        case SVM_CONSTANT_TAG_INTEGER: {
            svm_class_int* typed_info = further;

            log_trace("-- Bytes : %08X", typed_info->bytes);

            break;
        }
        case SVM_CONSTANT_TAG_FLOAT: {
            svm_class_float* typed_info = further;

            log_trace("-- Bytes : %08X", typed_info->bytes);

            break;
        }
        case SVM_CONSTANT_TAG_LONG: {
            // Fuck. You. Mr. Long.
            svm_class_long* typed_info = further;

            log_trace("-- Low : %08X", typed_info->low);
            log_trace("-- High : %08X", typed_info->high);

            break;
        }
        case SVM_CONSTANT_TAG_DOUBLE: {
            svm_class_double* typed_info = further;

            log_trace("-- Low : %08X", typed_info->low);
            log_trace("-- High : %08X", typed_info->high);

            break;
        }
        case SVM_CONSTANT_TAG_NAME_AND_TYPE: {
            svm_class_name_and_type* typed_info = further;

            log_trace("-- Name Index : %d", typed_info->name_index);
            log_trace("-- Descriptor Index : %d", typed_info->descriptor_index);

            break;
        }
        case SVM_CONSTANT_TAG_UTF8: {
            svm_class_utf8* typed_info = further;

            log_trace("-- String : %s", typed_info->bytes);

            break;
        }
        case SVM_CONSTANT_TAG_METHOD_HANDLE: {
            svm_class_method_handle* typed_info = further;

            // TODO

            break;
        }
        case SVM_CONSTANT_TAG_METHOD_TYPE: {
            svm_class_method_type* typed_info = further;

            log_trace("-- Descriptor Index : %d", typed_info->descriptor_index);

            break;
        }
        case SVM_CONSTANT_TAG_CLASS_MODULE: {
            svm_class_class_module* typed_info = further;

            log_trace("-- Name Index : %d", typed_info->name_index);

            break;

        }
        case SVM_CONSTANT_TAG_CLASS_PACKAGE: {
            svm_class_class_package* typed_info = further;

            log_trace("-- Name Index : %d", typed_info->name_index);

        }
        default: {
            log_fatal("Unknown constant pool tag (%d, 0x%02X).", tag, tag);

            exit(EXIT_FAILURE);
        }
    }
}

