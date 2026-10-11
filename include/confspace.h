#ifndef NCONFSPACE_H
#define NCONFSPACE_H

#include <stdint.h>

uint32_t cs_read_dword(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
uint16_t cs_read_word(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);

#endif // NCONFSPACE_H
