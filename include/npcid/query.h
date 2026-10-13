#ifndef NPCIQUERY_H
#define NPCIQUERY_H

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

#define IPC_MAX_MSG 256ULL

#endif // NPCIQUERY_H
