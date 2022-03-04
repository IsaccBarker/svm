#ifndef SVM_CONSTANT_POOL
#define SVM_CONSTANT_POOL

#include <stdlib.h>

#include <svm_log.h>

#define SVM_ACC_CONSTANT_CLASS 7
#define SVM_ACC_CONSTANT_FIELD_REF 9
#define SVM_ACC_CONSTANT_METHOD_REF 10
#define SVM_ACC_CONSTANT_INTERFACE_METHOD_REF 11
#define SVM_ACC_CONSTANT_STRING 8
#define SVM_ACC_CONSTANT_INTEGER 3
#define SVM_ACC_CONSTANT_FLOAT  4
#define SVM_ACC_CONSTANT_LONG 5
#define SVM_ACC_CONSTANT_DOUBLE 6
#define SVM_ACC_CONSTANT_NAME_AND_TYPE 12
#define SVM_ACC_CONSTANT_UTF8 1
#define SVM_ACC_CONSTANT_METHOD_HANDLE 15
#define SVM_ACC_CONSTANT_METHOD_TYPE 16
#define SVM_ACC_CONSTANT_INVOKE_DYNAMIC 18

/**
 * An entry into the constant pool. The contense of info
 * varies with tag. These are listed below.
 * https://docs.oracle.com/javase/specs/jvms/se8/html/jvms-4.html
 *      CLASS (4.4.1)
 *      FIELD_REF (4.4.2)
 *      METHOD_REF (4.4.2)
 *      INTERACE_METHOD_REF (4.4.2)
 *      STRING (4.4.3)
 *      INTEGER (4.4.4)
 *      FLOAT (4.4.5)
 *      LONG (4.4.5)
 *      DOUBLE (4.4.6)
 *      NAME_AND_TYPE (4.4.7)
 *      UTF8 (4.4.8)
 *      METHOD_HANDLE (4.4.9)
 *      METHOD_TYPE (4.4.10)
 *      INVOKE_DYNAMICS (4.4.11)
 * For the current version (class demo), we don't need many
 * of of these.
 */
typedef struct cp_info_t {
    uint8_t tag;
    size_t info_length;
    uint8_t* info;
} cp_info;


size_t svm_constant_info_length(uint8_t tag, uint16_t first);

char* svm_constant_info_as_string(uint8_t tag, uint16_t first);

#endif /* CONSTANT_POOL */
