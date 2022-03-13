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

/** Verifies some elements of the version. Verifies version ranges, and make
 * sure the bytecode isn't compiled for a JVM supporting over Java SE 17.
 * For more information, view the text right beneath the table in section
 * 4.1-A. */
void svm_verify_version_validity(svm_class* class);

/** Gets the human readable version of the version in the class.
 * See the table in section 4.1-A. For example, 61 corasponds to
 * Java SE 17, 52 to Java SE 8, etc... Ignores the minor version. */
char* svm_get_human_java_version(svm_class* class);

#endif /* SVM_CLASS_VERSION_H */

