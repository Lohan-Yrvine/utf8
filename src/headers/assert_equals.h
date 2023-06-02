#ifndef ASSERT_EQUALS_H
#define ASSERT_EQUALS_H

#include <stdbool.h>
#include <stdint.h>

bool assert_decoding(uint32_t a, uint32_t b);
bool assert_encoding(char *a, char *b);

#endif
