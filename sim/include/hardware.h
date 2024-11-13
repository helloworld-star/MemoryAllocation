#ifndef HARDWARE_H
#define HARDWARE_H

#include "common.h"
#include "sim_common.h"

extern uint8_t filter[4];
extern uint32_t filter_len[4];

extern uint8_t external_act[act_row][act_col];

extern uint8_t external_filter[act_row * fil_num];

extern uint8_t IP_state[IP_NUM];

void init_act();

void init_filter();

void init_sim();

#endif
