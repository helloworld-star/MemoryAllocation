#ifndef IPCALL_H
#define IPCALL_H

#include "top.h"
#include "init.h"

void read_IP_state(struct IP *IPArray);

bool CheckBoundary(struct Blockarray *BlockArray, uint32_t len);

void load(struct Blockarray *BlockArray, struct IP_block_list *load_list, uint32_t ext_addr, uint32_t len, uint8_t IP_ID);

void conv(struct Blockarray *BlockArray, struct IP *IPArray, uint8_t IP_ID, uint32_t act_ID, uint32_t fil_ID, uint32_t out_addr);


#endif