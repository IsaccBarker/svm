#include <svm_class_version.h>

#include <svm_log.h>

#include <stdint.h>
#include <stdlib.h>

void impl_check_minor_status(uint16_t major, uint16_t minor);
void impl_check_incompatable_bytecode_by_version(uint16_t major);

uint16_t svm_class_get_major(svm_class* class, unsigned char* src, size_t offset) {
    class->major_version = (src[offset] << 8) + src[offset+1];

    return 2;
}

uint16_t svm_class_get_minor(svm_class* class, unsigned char* src, size_t offset) {
    class->minor_version = (src[offset] << 8) + src[offset+1];

    return 2;
}

void svm_account_for_preview_features(svm_class* class) {
    /* Specification: 4.1-A
     *  A class file is said to depend on the preview features of Java SE N (N ≥ 12) if
     *  it has a major_version that corresponds to Java SE N (according to Table 4.1-
     *  A) and a minor_version of 65535. */

    // 56 is the numeric value for Java 12.
    if (class->major_version >= 56 &&
            class->minor_version == 65535) {
        // Preview features nessisary.

        class->meta.feature_preview = 1;
    }

    class->meta.feature_preview = 0;
}

void impl_check_minor_status(uint16_t major_version, uint16_t minor_version) {
    if (major_version >= 45 &&
            major_version >= 55) {
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

    log_fatal("Major version is outside of 45-55 (inclusive), and has a non 0 minor version (%d.%d).",
            major_version, minor_version);
    exit(EXIT_FAILURE);

}

void impl_check_incompatable_bytecode_by_version(uint16_t major_version) {
    // We only care about bytecode that was compiled for a JVM past
    // Java SE 17. Mostly.
    // https://stackoverflow.com/questions/49445775/is-java-byte-code-always-forward-compatible

    if (major_version > 61) {
        log_fatal("The JVM bytecode was compiled for a version newer than Java SE 17.");
        exit(EXIT_FAILURE);
    }
}

void svm_verify_version_validity(svm_class* class) {
    impl_check_minor_status(class->major_version, class->minor_version);
    impl_check_incompatable_bytecode_by_version(class->major_version);
}

char* svm_get_human_java_version(svm_class* class) {
    // Trivia ;) : https://stackoverflow.com/questions/58467204/why-do-java-class-file-versions-start-from-45

    switch (class->major_version) {
        case 45: {
            return "1.0.2/1.1 (May 1996)";
        }

        case 46: {
            return "1.2 (Feb. 1997)";
        }

        case 47: {
            return "1.3 (Dec. 1998)";
        }

        case 48: {
            return "1.4 (May 2000)";
        }

        case 49: {
            return "5.0 (Sep. 2004)";
        }

        case 50: {
            return "6.0 (Dec. 2006)";
        }

        // From here on out, Java is under Oracle's control :(
        // Sun shouldn't have died, screw the .com bubble. I
        // guess they were kinda stupid persuing Sparc, when
        // x86 was the open defacto (if you can't tell I like
        // computer history).

        case 51: {
            return "7.0 (July 2011)";
        }

        case 52: {
            return "8.0 (March 2014)";
        }

        case 53: {
            return "9.0 (Sep. 2017)";
        }

        // From here on out, Java gets a new release
        // twice a year. Crazy!

        case 54: {
            return "10.0 (March, 2018)";
        }

        case 55: {
            return "11.0 (Sep. 2018)";
        }

        case 56: {
            return "12.0 (March 2019)";
        }

        case 57: {
            return "13.0 (Sep. 2019)";
        }

        case 58: {
            return "14.0 (March 2020)";
        }

        case 59: {
            return "15.0 (Sep. 2020)";
        }

        case 60: {
            return "16.0 (March. 2021)";
        }

        case 61: {
            return "17.0 (Sep. 2021)";
        }

        default: {
            log_fatal("Unknown Java version %d.", class->major_version);

            exit(EXIT_FAILURE);
        }
    }
}

