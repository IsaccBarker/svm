#include <svm_constant_pool.h>

#include <svm_log.h>

uint16_t svm_class_get_constant_pool_count(svm_class* class, unsigned char* src, size_t offset) {
    class->constant_pool_count = (src[offset] << 8) + src[offset+1];

    return 2;
}

uint16_t svm_class_get_constant_pool(svm_class* class, unsigned char* src, size_t offset) {
    (void)class;
    (void)src;
    (void)offset;

    for (size_t constant_index = 0; constant_index < class->constant_pool_count; constant_index++) {
    
    }

    return 0;
}

