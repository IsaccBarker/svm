#include <svm_class_version.h>

#include <stdint.h>
#include <stdlib.h>

uint16_t svm_class_get_major(svm_class* class, unsigned char* src, size_t offset) {
    class->major_version = (src[offset] << 8) + src[offset+1];

    return 2;
}

uint16_t svm_class_get_minor(svm_class* class, unsigned char* src, size_t offset) {
    class->minor_version = (src[offset] << 8) + src[offset+1];

    return 2;
}

void svm_account_for_preview_features(svm_class* class) {
    /* Specification: 4.1-A
     *  A class file is said to depend on the preview features of Java SE N (N ≥ 12) if
     *  it has a major_version that corresponds to Java SE N (according to Table 4.1-
     *  A) and a minor_version of 65535. */

    // 56 is the numeric value for Java 12.
    if (class->major_version >= 56 &&
            class->minor_version == 65535) {
        // Preview features nessisary.

        class->meta.feature_preview = 1;
    }

    class->meta.feature_preview = 0;
}

