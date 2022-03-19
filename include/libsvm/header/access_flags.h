#ifndef SVM_ACCESS_FLAGS_H
#define SVM_ACCESS_FLAGS_H

#include "../class.h"

#include <stdlib.h>

#define SVM_CLASS_ACCESS_PUBLIC_MASK     0x0001
#define SVM_CLASS_ACCESS_FINAL_MASK      0x0010
#define SVM_CLASS_ACCESS_SUPER_MASK      0x0020
#define SVM_CLASS_ACCESS_INTERFACE_MASK  0x0200
#define SVM_CLASS_ACCESS_ABSTRACT_MASK   0x0400
#define SVM_CLASS_ACCESS_SYNTHETIC_MASK  0x1000
#define SVM_CLASS_ACCESS_ANNOTATION_MASK 0x2000
#define SVM_CLASS_ACCESS_ENUM_MASK       0x4000
#define SVM_CLASS_ACCESS_MODULE_MASK     0x8000


/** Gets the access flags of a class.
 * \param class The class to put the result into.
 * \param src The source of the class binary.
 * \param offset The offset in which to look from.
 * \returns The number of bytes to jump forward by.
 */
int svm_class_get_access_flags(svm_class* class, unsigned char* src, size_t offset);

/** Gets the access flags as a string.
 * \param flags The flags to use.
 * \param out Where to store the output.
 * \returns What out was passed in as. Just a convienence.
 */
char* svm_class_get_access_flags_as_string(uint16_t flags, char* out);

#endif /* SVM_ACCESS_FLAGS_H */

