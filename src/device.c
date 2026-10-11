#include <nyvela/user/syslib.h>

#include "../include/confspace.h"
#include "../include/device.h"

static bool visited_buses[256] = {true};

pci_device_t *devices = NULL;
uint64_t devices_length = 0;
uint64_t devices_cap = 4;

bool append_device(pci_device_t dev) {
  if (!devices) {
    devices = malloc(sizeof(pci_device_t) * devices_cap);

    if (!devices) {
      return false;
    }
  }

  if (devices_length >= devices_cap) {
    uint64_t new_cap = devices_cap * 2;

    void *tmp = realloc(devices, sizeof(pci_device_t) * new_cap);

    if (!tmp) {
      return false;
    }

    devices = tmp;
  }

  devices[devices_length++] = dev;
  return true;
}

void check_device(uint8_t bus, uint8_t device) {
  uint8_t function = 0;

  uint16_t vendor_id = cs_read_word(bus, device, function, 0x00);
  if (vendor_id == 0xFFFF) return; // does not exist

  check_function(bus, device, function);
  
  uint8_t header_type = cs_read_word(bus, device, function, 0x0E) & 0xFF;

  if ((header_type & 0x80) != 0) {
    for (function = 1; function < 8; function++) {
      if (cs_read_word(bus, device, function, 0x00) != 0xFFFF) {
        check_function(bus, device, function);
      }
    }
  }
}

void check_bus(uint8_t bus) {
  if (visited_buses[bus]) 
    return;
  
  visited_buses[bus] = true;

  for (uint8_t device = 0; device < 32; device++) {
    check_device(bus, device);
  }
}

void check_function(uint8_t bus, uint8_t device, uint8_t function) {
  uint16_t class_reg = cs_read_word(bus, device, function, 0x0A);

  uint8_t sub_class = class_reg & 0xFF;
  uint8_t base_class = (class_reg >> 8) & 0xFF;
  uint8_t header_type = cs_read_word(bus, device, function, 0x0E) & 0xFF;
  
  pci_device_t dev = (pci_device_t){
    .bus = bus, .device = device, .function = function,
    .vendor_id = cs_read_word(bus, device, function, 0x00),
    .device_id = cs_read_word(bus, device, function, 0x02),
    .base_class = base_class, .sub_class = sub_class,
    .prog_if = (cs_read_word(bus, device, function, 0x08) >> 8) & 0xFF,
    .header_type = header_type
  };

  if (!append_device(dev)) {
    sys_exit(PCI_SCAN_FAIL);
  }

  if ((base_class == 0x6) && (sub_class == 0x04) && (header_type & 0x7F) == 1) {
    uint8_t secondary_bus = (cs_read_word(bus, device, function, 0x18) >> 8) & 0xFF;
    
    if (secondary_bus != 0 && secondary_bus != bus) {
      check_bus(secondary_bus);
    }
  }
}

void check_all_buses(void) {
  devices_length = 0;
  umemset(visited_buses, 0, sizeof(visited_buses));

  uint8_t header_type = cs_read_word(0, 0, 0, 0x0E) & 0xFF;

  if ((header_type & 0x80) == 0) {
    check_bus(0);
  } else {
    for (uint8_t function = 0; function < 8; function++) {
      if (cs_read_word(0, 0, function, 0x00) == 0xFFFF) 
        continue;
      
      check_bus(function);
    }
  }
}
