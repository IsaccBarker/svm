#include <libsvm/header/fields.h>

int svm_class_get_fields_count(svm_class* class, unsigned char* src, size_t offset) {
        class->fields_count = (src[offset] << 8) + src[offset+1];
}

