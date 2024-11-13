#include "hardware.h"

uint8_t filter[4] = {32, 64, 32, 64};
uint32_t filter_len[4] = {32*act_row, 64*act_row, 32*act_row, 64*act_row};

uint8_t external_act[act_row][act_col];

uint8_t external_filter[act_row * fil_num];

uint8_t IP_state[IP_NUM];


void init_act()
{
    uint32_t i, j;
    for(i = 0; i < act_row; i++)
    {
        for(j = 0; j < act_col; j++)
        {
            external_act[i][j] = i + j;
        }
    }

    return;
}

void init_filter()
{
    uint32_t i;
    for(i = 0; i < BLOCK_NUM * BLOCK_SIZE; i++)
    {
        external_filter[i] = i;
    }

    return;
}

void sim_load()
{
    IP_state[LS] = BUSY;
  

    IP_state[LS] = IDLE;
}

void sim_conv()
{
    IP_state[CONV] = BUSY;

    IP_state[CONV] = IDLE;

    return;
}

void init_sim()
{
    init_act();
    init_filter();
    return;
}