#ifndef SIM_H
#define SIM_H

#include "top.h"

#define act_col 3
#define act_row 1024

#define fil_num 192

extern uint8_t filter[4];

extern uint8_t external_act[act_row][act_col];

extern uint8_t external_filter[act_row * fil_num];

void init_act();

void init_filter();

void init_sim();

#endif
