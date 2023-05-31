#include <stdint.h>

#include "headers/utf8_decoder.h"

uint16_t utf8_deconde_two_bytes(uint16_t bytes) {
    uint8_t first_byte = bytes >> 6 | 0xC0;
    uint8_t second_byte = (bytes & 0x3F) | 0x80;
    uint16_t result = first_byte << 8 | second_byte;

    return result;
}

uint32_t utf8_decode_three_bytes(uint32_t bytes) {
    uint8_t first_byte = bytes >> 12 | 0xE0;
    uint8_t second_byte = ((bytes >> 6) & 0x3F) | 0x80;
    uint8_t third_byte = (bytes & 0x3F) | 0x80;
    uint32_t result = first_byte << 16 | second_byte << 8 | third_byte;

    return result;
}

uint32_t utf8_decode_four_bytes(uint32_t bytes) {
    uint8_t first_byte = bytes >> 18 | 0xF0;
    uint8_t second_byte = ((bytes >> 12) & 0x3F) | 0x80;
    uint8_t third_byte = ((bytes >> 6) & 0x3F) | 0x80;
    uint8_t fourth_byte = (bytes & 0x3F) | 0x80;
    uint32_t result = first_byte << 24 | second_byte << 16 | third_byte << 8 | fourth_byte;

    return result;
}

uint32_t utf8_decode(uint32_t bytes) {
    if (bytes <= 0x00007F) {
        return bytes;
    } else if (bytes <= 0x0007FF) {
        return utf8_deconde_two_bytes(bytes);
    } else if (bytes <= 0x00FFFF) {
        return utf8_decode_three_bytes(bytes);
    } else if (bytes <= 0x10FFFF) {
        return utf8_decode_four_bytes(bytes);
    }

    return 0xFFFFFFFF;
}