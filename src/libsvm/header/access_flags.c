#include <libsvm/header/access_flags.h>
#include <libsvm/log.h>

#include <stdlib.h>
#include <string.h>
#include <errno.h>

int svm_class_get_access_flags(svm_class* class, unsigned char* src, size_t offset) {
    class->access_flags = (src[offset] << 8) + src[offset+1];

    return 2;
}

char* svm_class_get_access_flags_as_string(uint16_t flags, char* out) {
    if ((SVM_CLASS_ACCESS_PUBLIC_MASK & flags) == SVM_CLASS_ACCESS_PUBLIC_MASK) {
        strncat(out, "PUBLIC ", sizeof("PUBLIC "));
    }

    if ((SVM_CLASS_ACCESS_FINAL_MASK & flags) == SVM_CLASS_ACCESS_FINAL_MASK) {
        strncat(out, "FINAL ", sizeof("FINAL "));
    }

    if ((SVM_CLASS_ACCESS_SUPER_MASK & flags) == SVM_CLASS_ACCESS_SUPER_MASK) {
        strncat(out, "SUPER ", sizeof("SUPER "));
    }

    if ((SVM_CLASS_ACCESS_INTERFACE_MASK & flags) == SVM_CLASS_ACCESS_INTERFACE_MASK) {
        strncat(out, "INTERFACE ", sizeof("INTERFACE "));
    }

    if ((SVM_CLASS_ACCESS_ABSTRACT_MASK & flags) == SVM_CLASS_ACCESS_ABSTRACT_MASK) {
        strncat(out, "ABSTRACT ", sizeof("ABSTRACT "));
    }

    if ((SVM_CLASS_ACCESS_SYNTHETIC_MASK & flags) == SVM_CLASS_ACCESS_SYNTHETIC_MASK) {
        strncat(out, "SYTHETIC ", sizeof("SYNTHETIC "));
    }

    if ((SVM_CLASS_ACCESS_ANNOTATION_MASK & flags) == SVM_CLASS_ACCESS_ANNOTATION_MASK) {
        strncat(out, "ANNOTATION ", sizeof("ANNOTATION "));
    }

    if ((SVM_CLASS_ACCESS_ENUM_MASK & flags) == SVM_CLASS_ACCESS_ENUM_MASK) {
        strncat(out, "ENUM ", sizeof("ENUM "));
    }

    if ((SVM_CLASS_ACCESS_MODULE_MASK & flags) == SVM_CLASS_ACCESS_MODULE_MASK) {
        strncat(out, "MODULE ", sizeof("MODULE "));
    }

    return out;
}

