#include <svm_constant_pool.h>

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

size_t svm_info_length(uint8_t tag) {
    switch (tag) {
        case SVM_ACC_CONSTANT_CLASS:
            return 1;
        case SVM_ACC_CONSTANT_FIELD_REF:
            return 2;
        case SVM_ACC_CONSTANT_METHOD_REF:
            return 2;
        case SVM_ACC_CONSTANT_INTERFACE_METHOD_REF:
            return 2;
        case SVM_ACC_CONSTANT_STRING:
            return 1;
        case SVM_ACC_CONSTANT_INTEGER:
            return 2;
        case SVM_ACC_CONSTANT_FLOAT:
            return 2;
        case SVM_ACC_CONSTANT_LONG:
            return 4;
        case SVM_ACC_CONSTANT_DOUBLE:
            return 4;
        case SVM_ACC_CONSTANT_NAME_AND_TYPE:
            return 2;
        case SVM_ACC_CONSTANT_UTF8:
            return -1;
        case SVM_ACC_CONSTANT_METHOD_HANDLE:
            return 1;
        case SVM_ACC_CONSTANT_METHOD_TYPE:
            return 1;
        case SVM_ACC_CONSTANT_INVOKE_DYNAMIC:
            return 2;
        default:
            log_fatal("Unknown constant pool tag (%d).", tag);

            exit(EXIT_FAILURE);
    }
}

