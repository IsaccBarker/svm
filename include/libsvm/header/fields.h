#ifndef SVM_FIELDS_H
#define SVM_FIELDS_H

#include "../class.h"

#include <stdlib.h>

/** Gets the number of fields from the JVM bytecode.
 * \param class The class to put the result into.
 * \param src The source of the class binary.
 * \param offset The offset in which to look from.
 * \returns The number of bytes to jump forward by.
 */
int svm_class_get_fields_count(svm_class* class, unsigned char* src, size_t offset);

#endif /* SVM_FIELDS_H */
