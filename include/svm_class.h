#ifndef SVM_CLASS
#define SVM_CLASS

#include <svm_attribute_info.h>
#include <svm_constant_pool.h>
#include <svm_field_info.h>

/**
 * Defines a class state machine for functions to modify
 */
typedef struct svm_class_t {
    char* class_str;
} svm_class;

/**
 * Stores the exact representation of the class file.
 * This isn't meant to be modified after it's creation.
 */
typedef struct svm_class_representation_t {
    unsigned int magic : 4;
    unsigned int minor_ver : 2;
    unsigned int major_ver : 2;
    unsigned int constant_pool_count : 2;
    // cp_info constant_pool[]; // TODO
    unsigned int access_flags : 2;
    unsigned int this_class : 2;
    unsigned int super_class : 2;
    unsigned int interfaces_count : 2;
    // unsigned int interfaces[]; // TODO
    unsigned int fields_count : 2;
    // field_info fields[]; // TODO;
    unsigned int methods_count : 2;
    // method_info methods[]; // TODO
    unsigned int attribute_count : 2;
    // attribute_info attributes[]; // TODO
} svm_class_representation;

/** 
 * Print a high level representation of the class.
 */
void svm_print_class_overview(svm_class_representation* r);

#endif /* SVM_CLASS */
