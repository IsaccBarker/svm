#ifndef SVM_MAGIC_H
#define SVM_MAGIC_H

#include <svm_class.h>

#include <stdlib.h>

/** Gets the magic number from a class.
 * \param class The class to put the result into.
 * \param src The source of the class binary.
 * \param offset The offset in which to look from.
 * \returns The number of bytes to jump forward by.
 */
int svm_class_get_magic(svm_class* class, unsigned char* src, size_t offset);

#endif /* SVM_MAGIC_H */

