#ifndef SVM_THIS_SUPER_H
#define SVM_THIS_SUPER_H

#include "../class.h"

#include <stdlib.h>

/** Gets the current and super class from the
 * class file.
 * \param class The class to put the result into.
 * \param src The source of the class binary.
 * \param offset The offset in which to look from.
 * \returns The number of bytes to jump forward by.
 */
int svm_class_get_this_super(svm_class* class, unsigned char* src, size_t offset);

#endif /* SVM_THIS_SUPER_H */
