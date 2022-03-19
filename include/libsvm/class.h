#ifndef SVM_CLASS_H
#define SVM_CLASS_H

typedef struct svm_class svm_class;

#include "class_meta.h"
#include "header/constant_pool.h"

#include <stdint.h>
#include <stdlib.h>

/** A representation of a class containing JVM bytecode.
 * In the specification, this is defined under the 4th chapter (4.0).
 * All of the members in this struct translate from/into a class file,
 * with the exception of \ref svm_class.meta, which includes metadata
 * about the class, such as if it needs preview features. */
struct svm_class {
    /// Metadata (see parent comment).
    svm_class_meta meta;

    /// The magic of the file. Should be 0xCAFEBABE.
    uint32_t magic;
    /// The minor version of the file (e.g. Java Version).
    uint16_t minor_version;
    /// The major version of the file (e.g. Java Version).
    uint16_t major_version;
    /// The number of constants in the constant pool.
    uint16_t constant_pool_count;
    /// The constant pool.
    svm_class_cp_info* constant_pool;
};

/** Parses a class file from it's source.
 * It's worth mentioning here that by source, we don't mean
 * the source code, but rather the binary contense of the class
 * file.
 * This function calls lots of other parsing functions. It's mainly
 * just a convenience wrapper, but it might do other stuff in the
 * future.
 *
 * \param src The binary of the class file in question.
 * \param length The size of the class file, in bytes. Used to allocate appropriate memory for \ref svm_class.
 * \returns A pointer to the class representation. Must be freed.
 */
svm_class* svm_parse_class(unsigned char* src, size_t length);

/** Dump the raw hexidecimal representation of the class. Useful
 * for debugging, and not much else.
 * \param src The binary of the class file in question.
 * \param length The size of the class file, in bytes.
 */
void svm_display_class_hex(unsigned char* src, size_t length);

/** Dumps an overview of the class.
 * Here, we dump all of what the \ref svm_class struct contains.
 * This is really only useful for debugging purposes, or if
 * you just want to look cool.
 *
 * \param class The parsed class file. If not initialized (parsed), the program will abort.
 * */
void svm_dump_class(svm_class* class);

#endif /* SVM_CLASS_H */

