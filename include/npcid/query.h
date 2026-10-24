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

typedef enum npcid_query_func {
  NPCID_GET_DEVICE,
  NPCID_GET_BAR
} npcid_query_func_t;

typedef struct npcid_dev_query {
  uint8_t base_class, sub_class, prog_if;
} npcid_dev_query_t;

typedef struct npcid_bar_query {
  uint8_t bus, dev, func, bar;
} npcid_bar_query_t;

typedef struct ipc_npcid_query {
  npcid_query_func_t func;
  
  union {
    npcid_dev_query_t dev_query;
    npcid_bar_query_t bar_query;
  } args;
} ipc_npcid_query_t;

#define IPC_MAX_MSG 256ULL

#endif // NPCIQUERY_H
