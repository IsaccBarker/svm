#ifndef SVM_CLASS_META_H
#define SVM_CLASS_META_H

#include <stdint.h>

/** This structure contains information that isn't
 * immediately available in the class file. Instead,
 * this contains values that are pre-calculated before
 * runtime (runtime refering to the execution of the
 * bytecode inside the VM). */
typedef struct {
    /// Whether we need preview features.
    uint8_t feature_preview;
} svm_class_meta;

#endif /* SVM_CLASS_META_H */

