#ifndef NPCIDEVICE_H
#define NPCIDEVICE_H

#include <stdint.h>

#define PCI_SCAN_FAIL 1

typedef struct pci_device {
  uint8_t bus;
  uint8_t device;
  uint8_t function;

  uint16_t vendor_id, device_id;

  uint8_t base_class, sub_class;
  uint8_t prog_if;
  uint8_t header_type;
} pci_device_t;

typedef struct ipc_device_query {
  uint8_t base_class, sub_class, prog_if;
} ipc_device_query_t;

extern pci_device_t *devices;
extern uint64_t devices_length;
extern uint64_t devices_cap;

void check_device(uint8_t bus, uint8_t device);
void check_function(uint8_t bus, uint8_t device, uint8_t func);
void check_bus(uint8_t bus);
void check_all_buses(void);

uint64_t get_bar_addr(uint8_t bus, uint8_t dev, uint8_t func, uint8_t bar);

bool append_device(pci_device_t dev);

#endif // NPCIDEVICE_H
