#ifndef SVM_ATTRIBUTE_INFO
#define SVM_ATTRIBUTE_INFO

typedef struct attribute_info_t {
    uint16_t name_index;
    uint32_t info_length;
    uint8_t* info;
} attribute_info;

#endif /* SVM_ATTRIBUTE_INFO */

