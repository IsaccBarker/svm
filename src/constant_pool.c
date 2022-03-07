#include <svm_constant_pool.h>

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <limits.h>

#include <svm_log.h>

int is_constant_info_tag(uint8_t tag) {
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

char* constant_info_as_string(uint8_t tag) {
    switch (tag) {
        case SVM_ACC_CONSTANT_CLASS:
            return "Class";
        case SVM_ACC_CONSTANT_FIELD_REF:
            return "Field Reference";
        case SVM_ACC_CONSTANT_METHOD_REF:
            return "Method Reference";
        case SVM_ACC_CONSTANT_INTERFACE_METHOD_REF:
            return "Interface Method Reference";
        case SVM_ACC_CONSTANT_STRING:
            return "String";
        case SVM_ACC_CONSTANT_INTEGER:
            return "Integer";
        case SVM_ACC_CONSTANT_FLOAT:
            return "Float";
        case SVM_ACC_CONSTANT_LONG:
            return "Long";
        case SVM_ACC_CONSTANT_DOUBLE:
            return "Double";
        case SVM_ACC_CONSTANT_NAME_AND_TYPE:
            return "Name & Type";
        case SVM_ACC_CONSTANT_UTF8:
            return "UTF 8";
        case SVM_ACC_CONSTANT_METHOD_HANDLE:
            return "Method Handle";
        case SVM_ACC_CONSTANT_METHOD_TYPE:
            return "Method Type";
        case SVM_ACC_CONSTANT_INVOKE_DYNAMIC:
            return "Invoke Dynamic";
        default:
            log_error("Unknown constant pool tag (%d).", tag);

            exit(EXIT_FAILURE);
    }
}

