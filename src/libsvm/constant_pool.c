#include <svm_constant_pool.h>

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <limits.h>

#include <svm_log.h>

int svm_is_constant_info_tag(uint8_t tag) {
    switch (tag) {
        case SVM_ACC_CONSTANT_CLASS:
            break;
        case SVM_ACC_CONSTANT_FIELD_REF:
            break;
        case SVM_ACC_CONSTANT_METHOD_REF:
            break;
        case SVM_ACC_CONSTANT_INTERFACE_METHOD_REF:
            break;
        case SVM_ACC_CONSTANT_STRING:
            break;
        case SVM_ACC_CONSTANT_INTEGER:
            break;
        case SVM_ACC_CONSTANT_FLOAT:
            break;
        case SVM_ACC_CONSTANT_LONG:
            break;
        case SVM_ACC_CONSTANT_DOUBLE:
            break;
        case SVM_ACC_CONSTANT_NAME_AND_TYPE:
            break;
        case SVM_ACC_CONSTANT_UTF8:
            break;
        case SVM_ACC_CONSTANT_METHOD_HANDLE:
            break;
        case SVM_ACC_CONSTANT_METHOD_TYPE:
            break;
        case SVM_ACC_CONSTANT_INVOKE_DYNAMIC:
            break;
        default:
            return 0;
    }

    return 1;
}

char* svm_constant_info_as_string(uint8_t tag) {
    switch (tag) {
        case SVM_ACC_CONSTANT_CLASS:
            return "CLASS";
        case SVM_ACC_CONSTANT_FIELD_REF:
            return "FIELD_REF";
        case SVM_ACC_CONSTANT_METHOD_REF:
            return "METHOD_REF";
        case SVM_ACC_CONSTANT_INTERFACE_METHOD_REF:
            return "INTERFACE_METHOD_REF";
        case SVM_ACC_CONSTANT_STRING:
            return "STRING";
        case SVM_ACC_CONSTANT_INTEGER:
            return "INTEGER";
        case SVM_ACC_CONSTANT_FLOAT:
            return "FLOAT";
        case SVM_ACC_CONSTANT_LONG:
            return "LONG";
        case SVM_ACC_CONSTANT_DOUBLE:
            return "DOUBLE";
        case SVM_ACC_CONSTANT_NAME_AND_TYPE:
            return "NAME_AND_TYPE";
        case SVM_ACC_CONSTANT_UTF8:
            return "UTF8";
        case SVM_ACC_CONSTANT_METHOD_HANDLE:
            return "METHOD_HANDLE";
        case SVM_ACC_CONSTANT_METHOD_TYPE:
            return "METHOD_TYPE";
        case SVM_ACC_CONSTANT_INVOKE_DYNAMIC:
            return "INVOKE_DYNAMIC";
        default:
            log_error("Unknown constant pool tag (%d).", tag);

            exit(EXIT_FAILURE);
    }
}

