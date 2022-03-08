#include <class_file.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <svm_log.h>

FILE* get_file_handle(char* class_file) {
    FILE* f = fopen(class_file, "rb");

    if (f == NULL) {
        log_fatal("Failed to read file %s: %s", class_file, strerror(errno));

        exit(EXIT_FAILURE);
    }

    return f;
}

size_t get_file_size(FILE* f) {
    size_t length;

    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);

    return length;
}

unsigned char* read_class_file(size_t length, FILE* f) {
    unsigned char* buffer = malloc(length);

    fread(buffer, length, 1, f);

    return buffer;
}

