#include <svm_constant_pool.h>

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <limits.h>

size_t svm_constant_info_length(uint8_t tag, uint16_t first) {
    switch (tag) {
        case SVM_ACC_CONSTANT_CLASS:
            return 3;
        case SVM_ACC_CONSTANT_FIELD_REF:
            return 5;
        case SVM_ACC_CONSTANT_METHOD_REF:
            return 5;
        case SVM_ACC_CONSTANT_INTERFACE_METHOD_REF:
            return 5;
        case SVM_ACC_CONSTANT_STRING:
            return 3;
        case SVM_ACC_CONSTANT_INTEGER:
            return 5;
        case SVM_ACC_CONSTANT_FLOAT:
            return 5;
        case SVM_ACC_CONSTANT_LONG:
            return 9;
        case SVM_ACC_CONSTANT_DOUBLE:
            return 9;
        case SVM_ACC_CONSTANT_NAME_AND_TYPE:
            return 5;
        case SVM_ACC_CONSTANT_UTF8:
            return 2 + first;
        case SVM_ACC_CONSTANT_METHOD_HANDLE:
            return 4;
        case SVM_ACC_CONSTANT_METHOD_TYPE:
            return 3;
        case SVM_ACC_CONSTANT_INVOKE_DYNAMIC:
            return 5;
        default:
            log_error("Unknown constant pool tag (%d).", tag);

            exit(EXIT_FAILURE);
    }
}

char* svm_constant_info_as_string(uint8_t tag, uint16_t first) {
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

