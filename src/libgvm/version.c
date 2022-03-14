#include <gvm_version.h>

#include <gvm_log.h>

#include <stdint.h>
#include <stdlib.h>

void impl_check_minor_status(uint16_t major, uint16_t minor);
void impl_check_incompatable_bytecode_by_version(uint16_t major);

uint16_t gvm_class_get_major(gvm_class* class, unsigned char* src, size_t offset) {
    class->major_version = (src[offset] << 8) + src[offset+1];

    return 2;
}

uint16_t gvm_class_get_minor(gvm_class* class, unsigned char* src, size_t offset) {
    class->minor_version = (src[offset] << 8) + src[offset+1];

    return 2;
}

void gvm_account_for_preview_features(gvm_class* class) {
    /* Specification: 4.1-A
     *  A class file is said to depend on the preview features of Java SE N (N ≥ 12) if
     *  it has a major_version that corresponds to Java SE N (according to Table 4.1-
     *  A) and a minor_version of 65535. */

    if (class->major_version >= SVM_JAVA_12_0 &&
            class->minor_version == 65535) {
        // Preview features nessisary.

        class->meta.feature_preview = 1;
    }

    class->meta.feature_preview = 0;
}

void impl_check_minor_status(uint16_t major_version, uint16_t minor_version) {
    if (major_version >= SVM_JAVA_1_0_2 &&
            major_version >= SVM_JAVA_11_0) {
        // Minor versions are allowed.

        // This looks pointless, and it is, but this
        // is just so we can expand on this if we need
        // to, and not have to be confused about where
        // to put it. Future me will thank now me! At
        // least from the reference point in time in which
        // I am experiencing right now, as I write this
        // comment.
        if (minor_version == 0) {
            return;
        } else if (minor_version != 0) {
            return;
        }
    }

    if (minor_version != 0) {
        log_fatal("Major version is outside of 45-55 (inclusive), and has a non 0 minor version (%d.%d).",
                major_version, minor_version);
        exit(EXIT_FAILURE);
    }

}

void impl_check_incompatable_bytecode_by_version(uint16_t major_version) {
    /** We only care about bytecode that was compiled for a JVM past
     * Java SE 17. Mostly; almost all bytecode is forwards compatable,
     * except really old bytecode, which really only are missing a few
     * opcodes. They really are like Microsoft in their quest for
     * backwards compatability.
     * https://stackoverflow.com/questions/49445775/is-java-byte-code-always-forward-compatible
     */

    if (major_version > SVM_JAVA_17_0) {
        log_fatal("The JVM bytecode was compiled for a version newer than Java SE 17.");
        exit(EXIT_FAILURE);
    }
}

void gvm_verify_version_validity(gvm_class* class) {
    impl_check_minor_status(class->major_version, class->minor_version);
    impl_check_incompatable_bytecode_by_version(class->major_version);
}

char* gvm_get_human_java_version(gvm_class* class) {
    // Trivia ;) : https://stackoverflow.com/questions/58467204/why-do-java-class-file-versions-start-from-45

    switch (class->major_version) {
        case SVM_JAVA_1_0_2: {
            return "1.0.2/1.1 (May 1996)";
        }

        case SVM_JAVA_1_2: {
            return "1.2 (Feb. 1997)";
        }

        case SVM_JAVA_1_3: {
            return "1.3 (Dec. 1998)";
        }

        case SVM_JAVA_1_4: {
            return "1.4 (May 2000)";
        }

        case SVM_JAVA_5_0: {
            return "5.0 (Sep. 2004)";
        }

        case SVM_JAVA_6_0: {
            return "6.0 (Dec. 2006)";
        }

        // From here on out, Java is under Oracle's control :(
        // Sun shouldn't have died, screw the .com bubble. I
        // guess they were kinda stupid persuing Sparc, when
        // x86 was the open defacto (if you can't tell I like
        // computer history).

        case SVM_JAVA_7_0: {
            return "7.0 (July 2011)";
        }

        case SVM_JAVA_8_0: {
            return "8.0 (March 2014)";
        }

        case SVM_JAVA_9_0: {
            return "9.0 (Sep. 2017)";
        }

        // From here on out, Java gets a new release
        // twice a year. Crazy!

        case SVM_JAVA_10_0: {
            return "10.0 (March, 2018)";
        }

        case SVM_JAVA_11_0: {
            return "11.0 (Sep. 2018)";
        }

        case SVM_JAVA_12_0: {
            return "12.0 (March 2019)";
        }

        case SVM_JAVA_13_0: {
            return "13.0 (Sep. 2019)";
        }

        case SVM_JAVA_14_0: {
            return "14.0 (March 2020)";
        }

        case SVM_JAVA_15_0: {
            return "15.0 (Sep. 2020)";
        }

        case SVM_JAVA_16_0: {
            return "16.0 (March. 2021)";
        }

        case SVM_JAVA_17_0: {
            return "17.0 (Sep. 2021)";
        }

        default: {
            log_fatal("Unknown Java version %d.", class->major_version);

            if (class->major_version > SVM_JAVA_17_0) {
                log_fatal("It looks like the specified Java version exceeds 61 (Java SE 17). Newer versions of Java are not allowed.");
            }

            exit(EXIT_FAILURE);
        }
    }
}

