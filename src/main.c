#include <nyvela/user/syslib.h>

#include "../include/device.h"

static uint64_t safe_uitoa(int64_t val, char *buf, uint64_t cap) {
  uint64_t converted_bytes = 0;

  if (!(converted_bytes = uitoa(val, buf, cap))) {
    char s[] = "Failed to convert integer to string. (safe_uitoa)";
    sys_write(1, s, sizeof(s) - 1);
  }

  return converted_bytes;
}

void prints(char *s) {
  uint64_t size = ustrlen(s);
  sys_write(1, s, size);
}

void print_device(pci_device_t dev) {
  char buf[24];
  uint64_t converted_bytes = 0;

  if (!(converted_bytes = safe_uitoa((int64_t)dev.bus, buf, sizeof(buf))))
    return;
  
  prints("Bus: ");
  sys_write(1, buf, converted_bytes);
  prints("\n");

  if (!(converted_bytes = safe_uitoa((int64_t)dev.device, buf, sizeof(buf))))
    return;
  
  prints("Device: ");
  sys_write(1, buf, converted_bytes);
  prints("\n");

  if (!(converted_bytes = safe_uitoa((int64_t)dev.function, buf, sizeof(buf))))
    return;
  
  prints("Function: ");
  sys_write(1, buf, converted_bytes);
  prints("\n");

  if (!(converted_bytes = safe_uitoa((int64_t)dev.vendor_id, buf, sizeof(buf))))
    return;
  
  prints("Vendor ID: ");
  sys_write(1, buf, converted_bytes);
  prints("\n");

  if (!(converted_bytes = safe_uitoa((int64_t)dev.device_id, buf, sizeof(buf))))
    return;
  
  prints("Device ID: ");
  sys_write(1, buf, converted_bytes);
  prints("\n");

  if (!(converted_bytes = safe_uitoa((int64_t)dev.base_class, buf, sizeof(buf))))
    return;
  
  prints("Base Class: ");
  sys_write(1, buf, converted_bytes);
  prints("\n");

  if (!(converted_bytes = safe_uitoa((int64_t)dev.sub_class, buf, sizeof(buf))))
    return;
  
  prints("Sub Class: ");
  sys_write(1, buf, converted_bytes);
  prints("\n");

  if (!(converted_bytes = safe_uitoa((int64_t)dev.prog_if, buf, sizeof(buf))))
    return;
  
  prints("Prog IF: ");
  sys_write(1, buf, converted_bytes);
  prints("\n");

  if (!(converted_bytes = safe_uitoa((int64_t)dev.header_type, buf, sizeof(buf))))
    return;
  
  prints("Header Type: ");
  sys_write(1, buf, converted_bytes);
  prints("\n\n");
}

void _start(void) {
  malloc_init();
  check_all_buses(); 
  
  char buf[] = "Press enter to continue...";
  char tmp = 0;

  for (uint64_t i = 0; i < devices_length; i++) {
    print_device(devices[i]);
  }

  sys_exit(0);
}
