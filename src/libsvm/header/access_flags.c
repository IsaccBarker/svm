#include <libsvm/header/access_flags.h>

#include <stdlib.h>

int svm_class_get_access_flags(svm_class* class, unsigned char* src, size_t offset) {
    class->access_flags = (src[offset] << 8) + src[offset+1];

    return 2;
}

