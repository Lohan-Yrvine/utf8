#include <stdbool.h>
#include <string.h>

#include "headers/assert_equals.h"

bool assert_decoding(uint32_t a, uint32_t b) {
    return a == b;
}

bool assert_encoding(char *a, char *b) {
    return strcmp(a, b) == 0;
}
