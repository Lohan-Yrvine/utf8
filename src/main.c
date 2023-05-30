#include <stdint.h>
#include <stdio.h>

#include "headers/utf8_encoder.h"
#include "headers/assert_equals.h"

int main(void) {
    // encode 1 byte
    printf("Test encode 0x00: %d\n", assert_equals(0x00, utf8_enconde(0x00)));
    printf("Test encode 0x24: %d\n", assert_equals(0x24, utf8_enconde(0x24)));
    printf("Test encode 0x7F: %d\n", assert_equals(0x7F, utf8_enconde(0x7F)));

    // encode 2 bytes
    printf("Test encode 0xA3: %d\n", assert_equals(0xC2A3, utf8_enconde(0xA3)));

    // encode 3 bytes

    // encode 4 bytes

    return 0;
}
