#ifndef SVM_CLASS_VERSION_H
#define SVM_CLASS_VERSION_H

#include <svm_class.h>

#include <stdint.h>
#include <stdlib.h>

/** Gets the major version of Java that a class was compiled for.
 * \param class The class to put the result into.
 * \param src The source of the class binary.
 * \param offset The offset in which to look from.
 * \returns The number of bytes to jump forward by.
 */
uint16_t svm_class_get_major(svm_class* class, unsigned char* src, size_t offset);

/** Gets the minor version of Java that a class was compiled for.
 * \param class The class to put the result into.
 * \param src The source of the class binary.
 * \param offset The offset in which to look from.
 * \returns The number of bytes to jump forward by.
 */
uint16_t svm_class_get_minor(svm_class* class, unsigned char* src, size_t offset);

/** Accounts for the possibilty of preview features
 * being present. In section 4.1-A of the specification,
 * preview features are listed as a possibility. Please
 * check the specification for more information.
 * \param class The class to put the result into, that was calculated using the same class. */
void svm_account_for_preview_features(svm_class* class);

#endif /* SVM_CLASS_VERSION_H */

