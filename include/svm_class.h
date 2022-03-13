#ifndef SVM_CLASS_H
#define SVM_CLASS_H

#include <stdint.h>

/** A representation of a class containing JVM bytecode.
 * In the specification, this is defined under the 4th chapter (4.0). */
typedef struct {
    uint32_t magic;
    uint16_t minor_version;
    uint16_t major_version;
    uint16_t constant_pool_count;
} svm_constant_pool_entry ;

#endif /* SVM_CLASS_H */

