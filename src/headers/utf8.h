#ifndef UTF8_ENCODER_H
#define UTF8_ENCODER_H

#include <stdint.h>

uint32_t utf8_decode(char *bytes);

char* utf8_encode(uint32_t bytes);

#endif
