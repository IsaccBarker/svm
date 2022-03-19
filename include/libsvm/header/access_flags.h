#ifndef SVM_ACCESS_FLAGS_H
#define SVM_ACCESS_FLAGS_H

#include "../class.h"

#include <stdlib.h>

/** Gets the access flags of a class.
 * \param class The class to put the result into.
 * \param src The source of the class binary.
 * \param offset The offset in which to look from.
 * \returns The number of bytes to jump forward by.
 */
int svm_class_get_acess_flags(svm_class* class, unsigned char* src, size_t offset);

#endif /* SVM_ACCESS_FLAGS_H */

