#ifndef HARDWARE_H
#define HARDWARE_H

#include "common.h"
#include "sim_common.h"

extern uint8_t ext_act[act_row][act_col];
extern uint8_t ext_filter[act_row * fil_num];
extern uint8_t int_mem[BLOCK_NUM * BLOCK_SIZE];

extern uint8_t IP_state[IP_NUM];

void init_act();
void init_filter();
void init_sim();

void sim_load(struct BLOCK_Bundle mem_bundle);

#endif
