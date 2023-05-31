#include <stdint.h>
#include <stdio.h>

#include "headers/utf8_decoder.h"
#include "headers/assert_equals.h"

int main(void) {
    printf("Testing 1 byte decoding...\n");
    printf("Test: decode 0x00: %d\n", assert_equals(0x00, utf8_decode(0x00)));
    printf("Test: decode 0x24: %d\n", assert_equals(0x24, utf8_decode(0x24)));
    printf("Test: decode 0x7F: %d\n", assert_equals(0x7F, utf8_decode(0x7F)));

    printf("\nTesting 2 bytes decoding...\n");
    printf("Test: decode 0x080: %d\n", assert_equals(0xC280, utf8_decode(0x080)));
    printf("Test: decode 0x0A3: %d\n", assert_equals(0xC2A3, utf8_decode(0x0A3)));
    printf("Test: decode 0x418: %d\n", assert_equals(0xD098, utf8_decode(0x418)));
    printf("Test: decode 0x7FF: %d\n", assert_equals(0xDFBF, utf8_decode(0x7FF)));

    printf("\nTesting 3 bytes decoding...\n");
    printf("Test: decode 0x0800: %d\n", assert_equals(0xE0A080, utf8_decode(0x0800)));
    printf("Test: decode 0x0939: %d\n", assert_equals(0xE0A4B9, utf8_decode(0x0939)));
    printf("Test: decode 0x20AC: %d\n", assert_equals(0xE282AC, utf8_decode(0x20AC)));
    printf("Test: decode 0xD55C: %d\n", assert_equals(0xED959C, utf8_decode(0xD55C)));
    printf("Test: decode 0xFFFF: %d\n", assert_equals(0xEFBFBF, utf8_decode(0xFFFF)));

    printf("\nTesting 4 bytes decoding...\n");
    printf("Test: decode 0x010000: %d\n", assert_equals(0xF0908080, utf8_decode(0x010000)));
    printf("Test: decode 0x010348: %d\n", assert_equals(0xF0908D88, utf8_decode(0x010348)));
    printf("Test: decode 0x10FFFF: %d\n", assert_equals(0xF48FBFBF, utf8_decode(0x10FFFF)));

    return 0;
}
