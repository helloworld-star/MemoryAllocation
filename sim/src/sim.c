#include "sim.h"

uint8_t filter[4] = {32, 64, 32, 64};

uint8_t external_act[act_row][act_col];

uint8_t external_filter[act_row * fil_num];

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

void init_sim()
{
    init_act();
    init_filter();
    return;
}