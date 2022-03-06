#ifndef SVM_CLASS
#define SVM_CLASS

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

#include <attribute_info.h>
#include <method_info.h>
#include <constant_pool.h>
#include <field_info.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

/**
 * Defines a class state machine for functions to modify
 */
typedef struct class_t {
    char* class_str;
} class;

/**
 * Stores the exact representation of the class file.
 * This isn't meant to be modified after it's creation.
 * https://docs.oracle.com/javase/specs/jvms/se8/html/jvms-4.html
 */
typedef struct {
    uint32_t magic;
    uint16_t minor_ver;
    uint16_t major_ver;
    uint16_t constant_pool_count;
    cp_info* constant_pool;
    uint16_t access_flags;
    uint16_t this_class;
    uint16_t super_class;
    uint16_t interfaces_count;
    // uint16_t interfaces[]; // TODO
    uint16_t fields_count;
    // field_info fields[]; // TODO;
    uint16_t methods_count;
    method_info* methods; // TODO
    uint16_t attribute_count;
    // attribute_info attributes[]; // TODO
} class_representation;

/**
 * Initializes and runs the virtual machine
 */
class_representation* parse_class_file(size_t file_length, unsigned char* data);

/**
 * Prints out the class in indented hexadecimal form.
 */
void display_class_hex(unsigned char* data, size_t file_length);

/** 
 * Print a high level representation of the class.
 */
void print_class_overview(class_representation* r);

#endif /* SVM_CLASS */

