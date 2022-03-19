#include <libsvm/header/interface.h>

int svm_class_get_interfaces_count(svm_class* class, unsigned char* src, size_t offset) {
    class->interfaces_count = (src[offset] << 8) + src[offset+1];

    return 2;
}

int svm_class_get_interfaces(svm_class* class, unsigned char* src, size_t offset) {
    // TODO: Actually test this. I'm testing this on bytecode that doesn't
    // need anything interface related, so this could fail... FYI!
    for (int i = 0; i < class->interfaces_count; i++) {
        class->interfaces[i] = src[offset+i];
    }

    return class->interfaces_count;
}

