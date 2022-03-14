#include <gvm_magic.h>

#include <stdlib.h>

int gvm_class_get_magic(gvm_class* class, unsigned char* src, size_t offset) {
    class->magic = (src[offset] << 24) +
        (src[offset+1] << 16) +
        (src[offset+2] << 8) +
        (src[offset+3]);

    return 4;
}

