#include <stdint.h>
#include <stdio.h>

#include "headers/utf8.h"
#include "headers/assert_equals.h"

int main(void) {
    printf("Testing UTF-8 decoding...\n");
    printf("Testing [U+00, U+7F] limit decoding...\n");
    printf("Test: decode U+00: %d\n", assert_equals(0x00, utf8_decode("U+00")));
    printf("Test: decode U+24: %d\n", assert_equals(0x24, utf8_decode("U+24")));
    printf("Test: decode U+7F: %d\n", assert_equals(0x7F, utf8_decode("U+7F")));

    printf("\nTesting [U+080, U+7FF] limit decoding...\n");
    printf("Test: decode U+080: %d\n", assert_equals(0xC280, utf8_decode("U+080")));
    printf("Test: decode U+0A3: %d\n", assert_equals(0xC2A3, utf8_decode("U+0A3")));
    printf("Test: decode U+418: %d\n", assert_equals(0xD098, utf8_decode("U+418")));
    printf("Test: decode U+7FF: %d\n", assert_equals(0xDFBF, utf8_decode("U+7FF")));

    printf("\nTesting [U+0800, U+FFFF] limit decoding...\n");
    printf("Test: decode U+0800: %d\n", assert_equals(0xE0A080, utf8_decode("U+0800")));
    printf("Test: decode U+0939: %d\n", assert_equals(0xE0A4B9, utf8_decode("U+0939")));
    printf("Test: decode U+20AC: %d\n", assert_equals(0xE282AC, utf8_decode("U+20AC")));
    printf("Test: decode U+D55C: %d\n", assert_equals(0xED959C, utf8_decode("U+D55C")));
    printf("Test: decode U+FFFF: %d\n", assert_equals(0xEFBFBF, utf8_decode("U+FFFF")));

    printf("\nTesting [U+010000, U+10FFFF] limit decoding...\n");
    printf("Test: decode U+010000: %d\n", assert_equals(0xF0908080, utf8_decode("U+010000")));
    printf("Test: decode U+010348: %d\n", assert_equals(0xF0908D88, utf8_decode("U+010348")));
    printf("Test: decode U+10FFFF: %d\n", assert_equals(0xF48FBFBF, utf8_decode("U+10FFFF")));

    printf("\nTesting out of limit decoding...\n");
    printf("Test: decode U+110000: %d\n", assert_equals(0xFFFFFFFF, utf8_decode("U+110000")));
    printf("Test: decode U+591775: %d\n", assert_equals(0xFFFFFFFF, utf8_decode("U+591775")));
    printf("Test: decode U+670956: %d\n", assert_equals(0xFFFFFFFF, utf8_decode("U+670956")));
    printf("Test: decode U+FFFFFF: %d\n", assert_equals(0xFFFFFFFF, utf8_decode("U+FFFFFF")));

    return 0;
}
