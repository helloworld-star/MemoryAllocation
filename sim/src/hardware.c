#include "hardware.h"

uint8_t ext_act[INPUT_LEN];
uint8_t ext_filter[FILTER_TOTAL_LEN];
uint8_t int_mem[BLOCK_NUM * BLOCK_SIZE];

uint8_t IP_state[IP_NUM];

void init_act()
{
    uint32_t i, j = 0;
    for(i = 0; i < INPUT_LEN; i++)
    {
        ext_act[i] = j;
        j++;
        j = j == 20 ? 0 : j;
    }

    return;
}

void init_filter()
{
    uint32_t i, j = 0;
    for(i = 0; i < FILTER_TOTAL_LEN; i++)
    {
        ext_filter[i] = j;
        j++;
        j = j == 10 ? 0 : j;
    }

    return;
}

void init_int_mem()
{
    uint32_t i;
    for(i = 0; i < BLOCK_NUM * BLOCK_SIZE; i++)
    {
        int_mem[i] = 0;
    }

    return;
}

void sim_load(struct Blk_Bundle blk_bundle)
{
    IP_state[LS] = BUSY;
    // printf("Len: %ld\n",  (uint64_t)(blk_bundle.len));
    for (uint64_t i = 0; i < blk_bundle.len; i++) 
    {
        blk_bundle.int_addr[i] = blk_bundle.ext_addr[i];
            
        // printf("int_value: %ld\n",  (uint64_t)(blk_bundle.int_addr[i]));
        // printf("ext_value: %ld\n",  (uint64_t)(blk_bundle.ext_addr[i]));
    }
    IP_state[LS] = IDLE;
}

void sim_conv(struct Conv_Bundle conv_bundle)
{
    IP_state[CONV] = BUSY;
    
    uint32_t input_dim = conv_bundle.act_len / act_row; // act_len 应等于 act_row * input_dim
    uint32_t filter_num = conv_bundle.fil_len / input_dim; // fil_len 应等于 filter_num * input_dim
    printf("Input dim: %d, Filter num: %d\n", input_dim, filter_num);

    for (uint32_t i = 0; i < act_row; i++) 
    {
        for (uint32_t j = 0; j < filter_num; j++)
        {
            conv_bundle.out_addr[i * filter_num + j] = 0; 
            for (uint32_t k = 0; k < input_dim; k++) 
            {  
                conv_bundle.out_addr[i * filter_num + j] += conv_bundle.act_addr[i * input_dim + k] * conv_bundle.fil_addr[j * input_dim + k];
            }
        }
    }


    IP_state[CONV] = IDLE;

    return;
}


void init_sim()
{
    init_act();
    init_filter();
    init_int_mem();
    return;
}