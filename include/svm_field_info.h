#ifndef SVM_FIELD_INFO
#define SVM_FIELD_INFO

/** Declared public; may be accessed from outside its package. */
#define SVM_FIELD_FLAG_ACC_PUBLIC 0x0001

/** Declared private; usable only within the defining class. */
#define SVM_FIELD_FLAG_ACC_PRIVATE 0x0002

/** Declared protected; may be accessed within subclasses. */
#define SVM_FIELD_FLAG_ACC_PROTECTED 0x0004

/** Declared static. */
#define SVM_FIELD_FLAG_ACC_STATIC 0x0008

/** Declared final; never directly assigned to after object construction (JLS §17.5). */
#define SVM_FIELD_FLAG_ACC_FINAL 0x0010

/** Declared volatile; cannot be cached. */
#define SVM_FIELD_FLAG_ACC_VOLATILE 0x0040

/** Declared transient; not written or read by a persistent object manager. */
#define SVM_FIELD_FLAG_ACC_TRANSIENT 0x0080

/** Declared synthetic; not present in the source code. */
#define SVM_FIELD_FLAG_ACC_SYNTHETIC 0x1000

/** Declared as an element of an enum. */
#define SVM_FIELD_FLAG_ACC_ENUM 0x4000

typedef struct {
    unsigned int access_flags : 2;
    unsigned int name_index : 2;
    unsigned int descriptor_index : 2;
    unsigned int attributes_count : 2;
    svm_class_attribute_info* attributes; // TODO
} svm_class_field_info;

#endif /* SVM_FIELD_INFO */

