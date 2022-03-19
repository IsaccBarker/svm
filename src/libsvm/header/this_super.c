#include <libsvm/header/this_super.h>

int svm_class_get_this_super(svm_class* class, unsigned char* src, size_t offset) {
    class->this_class = (src[offset] << 8) + src[offset+1];
    class->super_class = (src[offset+2] << 8) + src[offset+3];

    return 4;
}

