#ifndef HARDWARE_H
#define HARDWARE_H

#include "common.h"
#include "sim_common.h"

extern uint8_t ext_act[INPUT_LEN];
extern uint8_t ext_filter[FILTER_TOTAL_LEN];
extern uint8_t int_mem[BLOCK_NUM * BLOCK_SIZE];

extern uint8_t IP_state[IP_NUM];

void init_act();
void init_filter();
void init_sim();

void sim_load(struct Blk_Bundle blk_bundle);
void sim_conv(struct Conv_Bundle conv_bundle);

#define BLOCK(i) (&int_mem[(i) * BLOCK_SIZE])

#endif
