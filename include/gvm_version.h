#ifndef SVM_CLASS_VERSION_H
#define SVM_CLASS_VERSION_H

#include <gvm_class.h>

#include <stdint.h>
#include <stdlib.h>

#define SVM_JAVA_1_0_2 45
#define SVM_JAVA_1_2 46
#define SVM_JAVA_1_3 47
#define SVM_JAVA_1_4 48
#define SVM_JAVA_5_0 49
#define SVM_JAVA_6_0 50
#define SVM_JAVA_7_0 51
#define SVM_JAVA_8_0 52
#define SVM_JAVA_9_0 53
#define SVM_JAVA_10_0 54
#define SVM_JAVA_11_0 55
#define SVM_JAVA_12_0 56
#define SVM_JAVA_13_0 57
#define SVM_JAVA_14_0 58
#define SVM_JAVA_15_0 59
#define SVM_JAVA_16_0 60
#define SVM_JAVA_17_0 61

/** Gets the major version of Java that a class was compiled for.
 * \param class The class to put the result into.
 * \param src The source of the class binary.
 * \param offset The offset in which to look from.
 * \returns The number of bytes to jump forward by.
 */
uint16_t gvm_class_get_major(gvm_class* class, unsigned char* src, size_t offset);

/** Gets the minor version of Java that a class was compiled for.
 * \param class The class to put the result into.
 * \param src The source of the class binary.
 * \param offset The offset in which to look from.
 * \returns The number of bytes to jump forward by.
 */
uint16_t gvm_class_get_minor(gvm_class* class, unsigned char* src, size_t offset);

/** Accounts for the possibilty of preview features
 * being present. In section 4.1-A of the specification,
 * preview features are listed as a possibility. Please
 * check the specification for more information.
 * \param class The class to put the result into, that was calculated using the same class. */
void gvm_account_for_preview_features(gvm_class* class);

/** Verifies some elements of the version. Verifies version ranges, and make
 * sure the bytecode isn't compiled for a JVM supporting over Java SE 17.
 * For more information, view the text right beneath the table in section
 * 4.1-A. */
void gvm_verify_version_validity(gvm_class* class);

/** Gets the human readable version of the version in the class.
 * See the table in section 4.1-A. For example, 61 corasponds to
 * Java SE 17, 52 to Java SE 8, etc... Ignores the minor version. */
char* gvm_get_human_java_version(gvm_class* class);

#endif /* SVM_CLASS_VERSION_H */

