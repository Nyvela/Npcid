#include <nyvela/arch/x86_64/asm/io.h>
#include <nyvela/user/syslib.h>
#include "../include/confspace.h"

uint32_t cs_read_dword(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
  return sys_call(SYS_PCI_CONF_READ32, bus, slot, func, offset);
}

uint16_t cs_read_word(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
  uint32_t value = cs_read_dword(bus, slot, func, offset);
  return (uint16_t)(value >> ((offset & 2u) * 8u));
}
