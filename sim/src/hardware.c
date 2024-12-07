#include "hardware.h"

uint8_t ext_act[act_row][act_col];
uint8_t ext_filter[act_row * fil_num];
uint8_t int_mem[BLOCK_NUM * BLOCK_SIZE];

uint8_t IP_state[IP_NUM];

void init_act()
{
    uint32_t i, j;
    for(i = 0; i < act_row; i++)
    {
        for(j = 0; j < act_col; j++)
        {
            ext_act[i][j] = i + j;
        }
    }

    return;
}

void init_filter()
{
    uint32_t i;
    for(i = 0; i < BLOCK_NUM * BLOCK_SIZE; i++)
    {
        ext_filter[i] = i;
    }

    return;
}

void sim_load(struct BLOCK_Bundle mem_bundle)
{
    IP_state[LS] = BUSY;
    for (uint64_t i = 0; i < mem_bundle.len; i++) 
    {
        // printf("mem_bundle.len: %ld\n",  (uint64_t)(mem_bundle.len));
        // printf("ext_addr: %ld\n",  (uint64_t)(mem_bundle.int_addr[i]));
        // printf("i: %ld\n",  (uint64_t)(i));
        mem_bundle.int_addr[i] = mem_bundle.ext_addr[i];
    }

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