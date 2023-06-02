#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "headers/utf8.h"

uint16_t utf8_decode_two_bytes(uint16_t hex) {
    uint8_t byte1 = hex >> 6 | 0xC0;
    uint8_t byte2 = (hex & 0x3F) | 0x80;
    uint16_t result = byte1 << 8 | byte2;

    return result;
}

uint32_t utf8_decode_three_bytes(uint32_t hex) {
    uint8_t byte1 = hex >> 12 | 0xE0;
    uint8_t byte2 = ((hex >> 6) & 0x3F) | 0x80;
    uint8_t byte3 = (hex & 0x3F) | 0x80;
    uint32_t result = byte1 << 16 | byte2 << 8 | byte3;

    return result;
}

uint32_t utf8_decode_four_bytes(uint32_t hex) {
    uint8_t byte1 = hex >> 18 | 0xF0;
    uint8_t byte2 = ((hex >> 12) & 0x3F) | 0x80;
    uint8_t byte3 = ((hex >> 6) & 0x3F) | 0x80;
    uint8_t byte4 = (hex & 0x3F) | 0x80;
    uint32_t result = byte1 << 24 | byte2 << 16 | byte3 << 8 | byte4;

    return result;
}

uint32_t utf8_decode(char *code) {
    uint32_t hex_value = strtoul(code+2, NULL, 16);

    if (hex_value <= 0x7F) {
        return hex_value;
    } else if (hex_value <= 0x7FF) {
        return utf8_decode_two_bytes(hex_value);
    } else if (hex_value <= 0xFFFF) {
        return utf8_decode_three_bytes(hex_value);
    } else if (hex_value <= 0x10FFFF) {
        return utf8_decode_four_bytes(hex_value);
    }

    return 0xFFFFFFFF;
}

bool two_bytes_validation(uint16_t hex) {
    uint8_t byte1 = hex >> 8;
    uint8_t byte2 = hex;

    return (byte1 <= 0xDF) && (byte2 <= 0xBF);
}

bool three_bytes_validation(uint32_t hex) {
    uint8_t byte1 = hex >> 16;
    uint8_t byte2 = hex >> 8;
    uint8_t byte3 = hex;

    return (byte1 <= 0xEF) && (byte2 <= 0xBF) && (byte3 <= 0xBF);
}

bool four_bytes_validation(uint32_t hex) {
    uint8_t byte1 = hex >> 24;
    uint8_t byte2 = hex >> 16;
    uint8_t byte3 = hex >> 8;
    uint8_t byte4 = hex;

    return (byte1 <= 0xF7) && (byte2 <= 0xBF) && (byte3 <= 0xBF) && (byte4 <= 0xBF);
}

bool is_valid_hex(uint32_t hex) {
    if (hex <= 0x7F) {
        return true;
    } else if (hex <= 0xDFBF) {
        return two_bytes_validation(hex);
    } else if (hex <= 0xEFBFBF) {
        return three_bytes_validation(hex);
    } else if (hex <= 0xF48FBFBF) {
        return four_bytes_validation(hex);
    }

    return false;
}

uint32_t encode_hex(uint32_t hex) {
    uint32_t formated_hex;
    if (hex <= 0x7F) {
        return hex;
    } else if (hex <= 0xDFBF) {
        uint8_t byte1 = (hex >> 8) & 0x1F;
        uint8_t byte2 = hex & 0x3F;
        formated_hex = byte1 << 6 | byte2;
    } else if (hex <= 0xEFBFBF) {
        uint8_t byte1 = (hex >> 16) & 0x0F;
        uint8_t byte2 = (hex >> 8) & 0x3F;
        uint8_t byte3 = hex & 0x3F;
        formated_hex = byte1 << 12 | byte2 << 6 | byte3;
    } else if (hex <= 0xF48FBFBF) {
        uint8_t byte1 = (hex >> 24) & 0x07;
        uint8_t byte2 = (hex >> 16) & 0x3F;
        uint8_t byte3 = (hex >> 8) & 0x3F;
        uint8_t byte4 = hex & 0x3F;
        formated_hex = byte1 << 18 | byte2 << 12 | byte3 << 6 | byte4;
    }

    return formated_hex;
}

char* utf8_encode(uint32_t hex) {
    if (!(is_valid_hex(hex))) {
        return "ERROR";
    }

    char hex_in_string[] = {
        '0', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
    };
    uint32_t encoded_hex = encode_hex(hex);

    uint8_t nyble1 = encoded_hex >> 20;
    uint8_t nyble2 = (encoded_hex >> 16) & 0xF;
    uint8_t nyble3 = (encoded_hex >> 12) & 0xF;
    uint8_t nyble4 = (encoded_hex >> 8) & 0xF;
    uint8_t nyble5 = (encoded_hex >> 4) & 0xF;
    uint8_t nyble6 = encoded_hex & 0xF;

    char *code = malloc(8);
    char *prefix = "U+";
    strcat(code, prefix);
    strncat(code, &hex_in_string[nyble1], 1);
    strncat(code, &hex_in_string[nyble2], 1);
    strncat(code, &hex_in_string[nyble3], 1);
    strncat(code, &hex_in_string[nyble4], 1);
    strncat(code, &hex_in_string[nyble5], 1);
    strncat(code, &hex_in_string[nyble6], 1);

    return code;
}
