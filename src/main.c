#include <nyvela/user/syslib.h>

#include "../include/device.h"
#include "../include/npcid/query.h"

void send_device(npcid_dev_query_t dev_query, uint64_t sender) {
  for (uint64_t i = 0; i < devices_length; i++) {
    if (devices[i].base_class == dev_query.base_class && devices[i].sub_class == dev_query.sub_class && devices[i].prog_if == dev_query.prog_if) {
      sys_ipc_send(sender, &devices[i], sizeof(pci_device_t));
    }
  }
}

void send_bar(npcid_bar_query_t bar_query, uint64_t sender) {
  uint64_t addr = 0;
  
  if (bar_query.bar <= 5) 
    addr = get_bar_addr(bar_query.bus, bar_query.dev, bar_query.func, 0x10 + bar_query.bar * 4);

  sys_ipc_send(sender, &addr, sizeof(uint64_t)); 
}

void _start(void) {
  malloc_init();
  check_all_buses(); 


  /*
  char buf[] = "Press enter to continue...";
  char tmp = 0;

  for (uint64_t i = 0; i < devices_length; i++) {
    print_device(devices[i]);
  }
  */
  
  uint8_t msg[IPC_MAX_MSG];
  uint64_t sender;

  while (true) {
    int64_t read = sys_ipc_poll(msg, sizeof(msg), &sender);

    if (read < sizeof(ipc_npcid_query_t)) {
      continue;
    }

    ipc_npcid_query_t query = *(ipc_npcid_query_t*)msg;
    
    switch (query.func) {
      case NPCID_GET_DEVICE:
        send_device(query.args.dev_query, sender);
        break;

      case NPCID_GET_BAR:
        send_bar(query.args.bar_query, sender);
        break;
    }
  }

  sys_exit(0);
}
