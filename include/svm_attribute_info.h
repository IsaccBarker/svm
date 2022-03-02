#ifndef SVM_ATTRIBUTE_INFO
#define SVM_ATTRIBUTE_INFO

typedef struct attribute_info_t {
    unsigned int attribute_name_index : 2;
    unsigned int attribute_length : 4;
    // unsigned int info[] : 1; // TODO
} attribute_info;

#endif /* SVM_ATTRIBUTE_INFO */

