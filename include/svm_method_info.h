#ifndef SVM_METHOD_INFO
#define SVM_METHOD_INFO

/** Declared public; may be accessed from outside its package. */
#define ACC_METHOD_ACCESS_PUBLIC 0x0001

/** Declared private; accessible only within the defining class. */
#define ACC_METHOD_ACCESS_PRIVATE 0x0002

/** Declared protected; may be accessed within subclasses. */
#define ACC_METHOD_ACCESS_PROTECTED 0x0004

/** Declared static. */
#define ACC_METHOD_ACCESS_STATIC 0x0008

/** Declared final; must not be overridden (§5.4.5). */
#define ACC_METHOD_ACCESS_FINAL 0x0010

/** Declared synchronized; invocation is wrapped by a monitor use. */
#define ACC_METHOD_ACCESS_SYNCHRONIZED 0x0020

/** A bridge method, generated by the compiler. */
#define ACC_METHOD_ACCESS_BRIDGE 0x0040

/** Declared with variable number of arguments. */
#define ACC_METHOD_ACCESS_VARARGS 0x0080

/** Declared native; implemented in a language other than Java. */
#define ACC_METHOD_ACCESS_NATIVE 0x0100

/** Declared abstract; no implementation is provided. */
#define ACC_METHOD_ACCESS_ABSTRACT 0x0400com

/** Declared strictfp; floating-point mode is FP-strict. */
#define ACC_METHOD_ACCESS_STRICT 0x0800

/** Declared synthetic; not present in the source code. */
#define ACC_METHOD_ACCESS_SYNTHETIC 0x1000

typedef struct {
    uint16_t access_flags;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t attributes_count;
    svm_class_attribute_info* attributes;
} svm_class_method_info;


#endif /* SVM_METHOD_INFO */

