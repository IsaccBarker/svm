#ifndef SVM_INTERFACES_H
#define SVM_INTERFACES_H

#include "../class.h"

#include <stdlib.h>

/** Gets the number of interfaces from class bytecode.
 * \param class The class to put the result into.
 * \param src The source of the class binary.
 * \param offset The offset in which to look from.
 * \returns The number of bytes to jump forward by.
 */
int svm_class_get_interfaces_count(svm_class* class, unsigned char* src, size_t offset);

/** Gets the interfaces from the class bytecode.
 * \param class The class to put the result into.
 * \param src The source of the class binary.
 * \param offset The offset in which to look from.
 * \returns The number of bytes to jump forward by.
 */
int svm_class_get_interfaces(svm_class* class, unsigned char* src, size_t offset);

#endif /* SVM_INTERFACES_H */

