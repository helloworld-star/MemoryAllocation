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
bool CheckBoundary(struct BlockArray *blockarray, uint8_t block_need);
void load(struct BlockArray *blockarray, struct IP_block_list *load_list, struct BlkCtrl_Bundle blk_bundle);
void conv(struct BlockArray *blockarray, struct IP_block_list *act_list, struct IP_block_list *filter_list, uint32_t output_len);

#endif