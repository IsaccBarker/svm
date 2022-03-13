#ifndef SVM_CONSTANT_POOL_H
#define SVM_CONSTANT_POOL_H

#include <svm_class.h>

#include <stdint.h>
#include <stdlib.h>

#define SVM_CONSTANT_TAG_UTF8 1
#define SVM_CONSTANT_TAG_INTEGER 3
#define SVM_CONSTANT_TAG_FLOAT 4
#define SVM_CONSTANT_TAG_LONG 5
#define SVM_CONSTANT_TAG_DOUBLE 6
#define SVM_CONSTANT_TAG_CLASS 7
#define SVM_CONSTANT_TAG_STRING 8
#define SVM_CONSTANT_TAG_FIELD_REF 9
#define SVM_CONSTANT_TAG_METHOD_REF 10
#define SVM_CONSTANT_TAG_INTERFACE_METHOD_REF 11
#define SVM_CONSTANT_TAG_NAME_AND_TYPE 12
#define SVM_CONSTANT_TAG_METHOD_HANDLE 15
#define SVM_CONSTANT_TAG_METHOD_TYPE 16
#define SVM_CONSTANT_TAG_INVOKE_DYNAMIC 18

#define SVM_METHOD_HANDLE_KIND_GET_FIELD 1
#define SVM_METHOD_HANDLE_KIND_GET_STATIC 2
#define SVM_METHOD_HANDLE_KIND_PUT_FIELD 3
#define SVM_METHOD_HANDLE_KIND_PUT_STATIC 4
#define SVM_METHOD_HANDLE_KIND_INVOKE_VIRTUAL 5
#define SVM_METHOD_HANDLE_KIND_INVOKE_STATIC 6
#define SVM_METHOD_HANDLE_KIND_INVOKE_SPECIAL 7
#define SVM_METHOD_HANDLE_KIND_NEW_INVOKE_SPECIAL 8
#define SVM_METHOD_HANDLE_KIND_INVOKE_INTERFACE 9

/**
 * An entry into the constant pool. The contense of info
 * varies based on the tag; see section 4.4 for more
 * information. It is worth noting that the specification
 * mentions an array of type uint8_t, which is not mentioned
 * here. Instead, we have a pointer to a structure that
 * better holds the individual properties required by each
 * tag. */
typedef struct {
    uint8_t tag;
    void* further;
} svm_class_cp_info;

typedef struct {
    uint16_t name_index;
} svm_class_class;

typedef struct {
    uint16_t class_index;
    uint16_t name_and_type_index;
} svm_class_field_ref;

typedef struct {
    uint16_t class_index;
    uint16_t name_and_type_index;
} svm_class_method_ref;

typedef struct {
    uint16_t class_index;
    uint16_t name_and_type_index;
} svm_class_interface_method_ref;

typedef struct {
    uint16_t string_index;
} svm_class_string;

typedef struct {
    uint32_t bytes;
} svm_class_int;

typedef struct {
    uint32_t bytes;
} svm_class_float;

typedef struct {
    uint32_t low;
    uint32_t high;
} svm_class_long;

typedef struct {
    uint32_t low;
    uint32_t high;
} svm_class_double;

typedef struct {
    uint16_t name_index;
    uint16_t descriptor_index;
} svm_class_name_and_type;

typedef struct {
    uint16_t length;
    uint8_t* bytes;
} svm_class_utf8;

typedef struct {
    uint8_t reference_kind;
    uint16_t reference_index;
} svm_class_method_handle;

typedef struct {
    uint16_t descriptor_index;
} svm_class_method_type;

typedef struct {
    uint16_t bootstrap_method_attr_index;
    uint16_t name_and_type_index;
} svm_class_dynamic;

typedef struct {
    uint16_t bootstrap_method_attr_index;
    uint16_t name_and_type_index;
} svm_class_invoke_dynamic;

/** Gets the number of constants in the constant pool.
 * \param class The class to put the result into.
 * \param src The source of the class binary.
 * \param offset The offset in which to look from.
 * \returns The number of bytes to jump forward by.
 */
uint16_t svm_class_get_constant_pool_count(svm_class* class, unsigned char* src, size_t offset);

/** Gets all the constants in the constant pool.
 * \param class The class to put the result into.
 * \param src The source of the class binary.
 * \param offset The offset in which to look from.
 * \returns The number of bytes to jump forward by.
 */
uint16_t svm_class_get_constant_pool(svm_class* class, unsigned char* src, size_t offset);

#endif /** SVM_CONSTANT_POOL_H */

