#ifndef SVM_CONSTANT_POOL_H
#define SVM_CONSTANT_POOL_H

typedef struct svm_class_cp_info svm_class_cp_info;

#include "../class.h"

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
#define SVM_CONSTANT_TAG_DYNAMIC 17
#define SVM_CONSTANT_TAG_INVOKE_DYNAMIC 18
#define SVM_CONSTANT_TAG_CLASS_MODULE 19
#define SVM_CONSTANT_TAG_CLASS_PACKAGE 20

#define SVM_METHOD_HANDLE_KIND_GET_FIELD 1
#define SVM_METHOD_HANDLE_KIND_GET_STATIC 2
#define SVM_METHOD_HANDLE_KIND_PUT_FIELD 3
#define SVM_METHOD_HANDLE_KIND_PUT_STATIC 4
#define SVM_METHOD_HANDLE_KIND_INVOKE_VIRTUAL 5
#define SVM_METHOD_HANDLE_KIND_INVOKE_STATIC 6
#define SVM_METHOD_HANDLE_KIND_INVOKE_SPECIAL 7
#define SVM_METHOD_HANDLE_KIND_NEW_INVOKE_SPECIAL 8
#define SVM_METHOD_HANDLE_KIND_INVOKE_INTERFACE 9

#define SVM_CONSTANT_TAG_SIZE_UTF8 sizeof(uint8_t*)
#define SVM_CONSTANT_TAG_SIZE_INTEGER 4
#define SVM_CONSTANT_TAG_SIZE_FLOAT 4
#define SVM_CONSTANT_TAG_SIZE_LONG 8
#define SVM_CONSTANT_TAG_SIZE_DOUBLE 8
#define SVM_CONSTANT_TAG_SIZE_CLASS 2
#define SVM_CONSTANT_TAG_SIZE_STRING 2
#define SVM_CONSTANT_TAG_SIZE_FIELD_REF 4
#define SVM_CONSTANT_TAG_SIZE_METHOD_REF 4
#define SVM_CONSTANT_TAG_SIZE_INTERFACE_METHOD_REF 4
#define SVM_CONSTANT_TAG_SIZE_NAME_AND_TYPE 4
#define SVM_CONSTANT_TAG_SIZE_METHOD_HANDLE 3
#define SVM_CONSTANT_TAG_SIZE_METHOD_TYPE 2

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
    uint16_t a;
} svm_class_constant_scheme_16;

typedef struct {
    uint16_t a;
    uint16_t b;
} svm_class_constant_scheme_16_16;

typedef struct {
    uint32_t a;
} svm_class_constant_scheme_32;

typedef struct {
    uint32_t a;
    uint32_t b;
} svm_class_constant_scheme_32_32;

typedef struct {
    uint8_t a;
} svm_class_constant_scheme_8;

typedef struct {
    uint8_t a;
    uint16_t b;
} svm_class_constant_scheme_8_16;

typedef struct {
    uint8_t* a;
} svm_class_constant_scheme_8ptr;

/** Get the size that the "payload" (info member)
 * is, in bytes. This will return the max on types that
 * do not have a fixed size, such as \ref svm_class_utf8.
 * \param tag The tag to get the corasponding info's size of.
 * \returns The size, in bytes. */
size_t svm_class_constant_tag_constant_to_size(uint8_t tag);

/** Gets a constant tag as a string. Useful for debugging,
 * but not much else.
 * \param tag The tag to get as a string.
 * \returns The string that the tag is.
 */
char* svm_class_constant_tag_as_string(uint8_t tag);

/** Initialized \ref info with the correct values, reading
 * from \ref src from offset \ref offset.
 * \param info The struct to write the result to.
 * \param src The source of the class binary.
 * \param offset The offset in which to look from.
 * \returns The number of bytes to jump forward by.
 */
uint16_t svm_class_constant_create_fixed_constant_entry(void* further, uint8_t tag, unsigned char* src, size_t offset);

/** Pretty prints the constant pool entry supplied.
 * \param info The struct to read from.
 * \param pool The entire constant pool.
 */
void svm_class_print_constant_entry(uint16_t tag, void* further, svm_class_cp_info* pool);

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

