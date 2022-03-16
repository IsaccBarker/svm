#ifndef SVM_CONSTANT_POOL_H
#define SVM_CONSTANT_POOL_H

typedef struct svm_class_cp_info svm_class_cp_info;

#include <svm_class.h>

#include <stdint.h>
#include <stdlib.h>
#include <limits.h>

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
 * tag.
 * The ones without a fixed size (e.g. the ones containing
 * a pointer to an array) don't nessisarly map 1 to 1. An
 * example of this is the UTF8 constant; the specification
 * defines it as having a size baked in, but we just use
 * a null terminator and disregard the size. */
struct svm_class_cp_info {
    uint8_t tag;
    void* further;
};

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

typedef struct {
    uint16_t name_index;
} svm_class_module;

typedef struct {
    uint16_t name_index;
} svm_class_package;

#define SVM_CONSTANT_TAG_SIZE_UTF8 sizeof(svm_class_utf8)
#define SVM_CONSTANT_TAG_SIZE_INTEGER sizeof(svm_class_int)
#define SVM_CONSTANT_TAG_SIZE_FLOAT sizeof(svm_class_float)
#define SVM_CONSTANT_TAG_SIZE_LONG sizeof(svm_class_long)
#define SVM_CONSTANT_TAG_SIZE_DOUBLE sizeof(svm_class_double)
#define SVM_CONSTANT_TAG_SIZE_CLASS sizeof(svm_class_class)
#define SVM_CONSTANT_TAG_SIZE_STRING sizeof(svm_class_string)
#define SVM_CONSTANT_TAG_SIZE_FIELD_REF sizeof(svm_class_field_ref)
#define SVM_CONSTANT_TAG_SIZE_METHOD_REF sizeof(svm_class_method_ref)
#define SVM_CONSTANT_TAG_SIZE_INTERFACE_METHOD_REF sizeof(svm_class_interface_method_ref)
#define SVM_CONSTANT_TAG_SIZE_NAME_AND_TYPE sizeof(svm_class_name_and_type)
#define SVM_CONSTANT_TAG_SIZE_METHOD_HANDLE sizeof(svm_class_method_handle)
#define SVM_CONSTANT_TAG_SIZE_METHOD_TYPE sizeof(svm_class_method_type)
#define SVM_CONSTANT_TAG_SIZE_INVOKE_DYNAMIC sizeof(svm_class_invoke_dynamic)

/** Get the size that the "payload" (info member)
 * is, in bytes. This will return the max on types that
 * do not have a fixed size, such as \ref svm_class_utf8.
 * \param tag The tag to get the corasponding info's size of.
 * \returns The size, in bytes. */
size_t svm_class_tag_constant_to_size(uint8_t tag);

/** Gets a constant tag as a string. Useful for debugging,
 * but not much else.
 * \param The tag to get as a string.
 * \returns The string that the tag is.
 */
char* svm_constant_tag_as_string(uint8_t tag);

/** Pretty prints the constant pool entry supplied.
 * \param info The struct to read from.
 */
void svm_class_print_constant_entry(svm_class_cp_info* info);

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

/** Gets the next constant in the constant pool. By
 * next, we really mean the constant starting at
 * \ref offset.
 * \param info The struct to write the results into.
 * \param src The source of the class binary.
 * \param offset The offset in which to look from.
 * \returns How many bytes to jump forward after reading.
 */
size_t svm_class_get_next_constant_entry(svm_class_cp_info* info, unsigned char* src, size_t offset);

/** Like \ref svm_class_get_next_constant_entry, but calculates
 * for the non-fixed size UTF8 constant. This is really just called
 * from \ref svm_class_get_next_constant_entry.
 * \param info The struct to write the results into.
 * \param src The source of the class binary.
 * \param offset The offset in which to look from.
 * \returns How many bytes to jump forward after reading. */
size_t svm_class_get_next_constant_entry_utf8(svm_class_cp_info* info, unsigned char* src, size_t offset);

#endif /** SVM_CONSTANT_POOL_H */

