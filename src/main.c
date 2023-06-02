#include <stdio.h>

#include "headers/utf8.h"
#include "headers/assert_equals.h"

int main(void) {
    printf("Testing UTF-8 decoding...\n");
    printf("Testing [U+00, U+7F] limit decoding...\n");
    printf("Test: decode U+00: %d\n", assert_decoding(0x00, utf8_decode("U+00")));
    printf("Test: decode U+24: %d\n", assert_decoding(0x24, utf8_decode("U+24")));
    printf("Test: decode U+7F: %d\n", assert_decoding(0x7F, utf8_decode("U+7F")));

    printf("\nTesting [U+080, U+7FF] limit decoding...\n");
    printf("Test: decode U+080: %d\n", assert_decoding(0xC280, utf8_decode("U+080")));
    printf("Test: decode U+0A3: %d\n", assert_decoding(0xC2A3, utf8_decode("U+0A3")));
    printf("Test: decode U+418: %d\n", assert_decoding(0xD098, utf8_decode("U+418")));
    printf("Test: decode U+7FF: %d\n", assert_decoding(0xDFBF, utf8_decode("U+7FF")));

    printf("\nTesting [U+0800, U+FFFF] limit decoding...\n");
    printf("Test: decode U+0800: %d\n", assert_decoding(0xE0A080, utf8_decode("U+0800")));
    printf("Test: decode U+0939: %d\n", assert_decoding(0xE0A4B9, utf8_decode("U+0939")));
    printf("Test: decode U+20AC: %d\n", assert_decoding(0xE282AC, utf8_decode("U+20AC")));
    printf("Test: decode U+D55C: %d\n", assert_decoding(0xED959C, utf8_decode("U+D55C")));
    printf("Test: decode U+FFFF: %d\n", assert_decoding(0xEFBFBF, utf8_decode("U+FFFF")));

    printf("\nTesting [U+010000, U+10FFFF] limit decoding...\n");
    printf("Test: decode U+010000: %d\n", assert_decoding(0xF0908080, utf8_decode("U+010000")));
    printf("Test: decode U+010348: %d\n", assert_decoding(0xF0908D88, utf8_decode("U+010348")));
    printf("Test: decode U+10FFFF: %d\n", assert_decoding(0xF48FBFBF, utf8_decode("U+10FFFF")));

    printf("\nTesting out of limit decoding...\n");
    printf("Test: decode U+110000: %d\n", assert_decoding(0xFFFFFFFF, utf8_decode("U+110000")));
    printf("Test: decode U+591775: %d\n", assert_decoding(0xFFFFFFFF, utf8_decode("U+591775")));
    printf("Test: decode U+670956: %d\n", assert_decoding(0xFFFFFFFF, utf8_decode("U+670956")));
    printf("Test: decode U+FFFFFF: %d\n", assert_decoding(0xFFFFFFFF, utf8_decode("U+FFFFFF")));

    printf("\nTesting UTF-8 encoding...\n");
    printf("Testing [U+00, U+7F] limit encoding...\n");
    printf("Test: encode 0x00: %d\n", assert_encoding("U+000000", utf8_encode(0x00)));
    printf("Test: encode 0x24: %d\n", assert_encoding("U+000024", utf8_encode(0x24)));
    printf("Test: encode 0x7F: %d\n", assert_encoding("U+00007F", utf8_encode(0x7F)));

    printf("\nTesting [U+080, U+7FF] limit encoding...\n");
    printf("Test: encode 0xC280: %d\n", assert_encoding("U+000080", utf8_encode(0xC280)));
    printf("Test: encode 0xC2A3: %d\n", assert_encoding("U+0000A3", utf8_encode(0xC2A3)));
    printf("Test: encode 0xD098: %d\n", assert_encoding("U+000418", utf8_encode(0xD098)));
    printf("Test: encode 0xDFBF: %d\n", assert_encoding("U+0007FF", utf8_encode(0xDFBF)));

    printf("\nTesting [U+0800, U+FFFF] limit encoding...\n");
    printf("Test: encode 0xE0A080: %d\n", assert_encoding("U+000800", utf8_encode(0xE0A080)));
    printf("Test: encode 0xE0A4B9: %d\n", assert_encoding("U+000939", utf8_encode(0xE0A4B9)));
    printf("Test: encode 0xE282AC: %d\n", assert_encoding("U+0020AC", utf8_encode(0xE282AC)));
    printf("Test: encode 0xED959C: %d\n", assert_encoding("U+00D55C", utf8_encode(0xED959C)));
    printf("Test: encode 0xEFBFBF: %d\n", assert_encoding("U+00FFFF", utf8_encode(0xEFBFBF)));

    printf("\nTesting [U+010000, U+10FFFF] limit encoding...\n");
    printf("Test: encode 0xF0908080: %d\n", assert_encoding("U+010000", utf8_encode(0xF0908080)));
    printf("Test: encode 0xF0908D88: %d\n", assert_encoding("U+010348", utf8_encode(0xF0908D88)));
    printf("Test: encode 0xF48FBFBF: %d\n", assert_encoding("U+10FFFF", utf8_encode(0xF48FBFBF)));

    printf("\nTesting out of limit encoding...\n");
    printf("Test: encode 0xF493FDE9: %d\n", assert_encoding("ERROR", utf8_encode(0xF493FDE9)));
    printf("Test: encode 0xF50B2E4C: %d\n", assert_encoding("ERROR", utf8_encode(0xF50B2E4C)));
    printf("Test: encode 0xF8CBB10A: %d\n", assert_encoding("ERROR", utf8_encode(0xF8CBB10A)));
    printf("Test: encode 0xFBE64816: %d\n", assert_encoding("ERROR", utf8_encode(0xFBE64816)));

    return 0;
}
