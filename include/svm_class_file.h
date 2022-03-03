#ifndef SVM_CLASS_FILE
#define SVM_CLASS_FILE

#include <stdio.h>

/**
 * Get a file handler for a file.
 */
FILE* svm_get_file_handle(char* class_file);

/**
 * Gets the size of the file that the handler points to.
 */
size_t svm_get_file_size(FILE* f);

/**
 * Read the class file because we need to load it into
 * memory to use it. Duh.
 */
unsigned char* svm_read_class_file(size_t length, FILE* f);

#endif /* SVM_CLASS_FILE */

