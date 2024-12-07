#ifndef IPCALL_H
#define IPCALL_H

#include "common.h"
#include "init.h"
#ifdef ENABLE_SIM_MODE
    #include "sim_common.h"
    #include "hardware.h"
    #include <assert.h>
#endif

void read_IP_state(struct IP *IPArray);
bool CheckBoundary(struct Blockarray *BlockArray, uint32_t block_need);
void load(struct Blockarray *blockArray, struct IP_block_list *load_list, struct EXT2INT_Bundle mem_bundle);
void conv(struct Blockarray *BlockArray, struct IP *IPArray, uint8_t IP_ID, uint32_t act_ID, uint32_t fil_ID, uint32_t out_addr);


#endif