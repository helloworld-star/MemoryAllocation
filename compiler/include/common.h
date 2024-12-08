#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define BLOCK_SIZE 4096 /* 4KB unit: Byte */
#define BLOCK_NUM 32
#define IP_NUM 2
#define CONV_LAYER 4

#define FIRST_BLOCK_ADDR 0x00000000
#define BLOCK_LAST_ADDRESS (FIRST_REG_ADDR + REG_NUM * BLOCK_SIZE - 1) 
#define FIRST_IP_ADDR (FIRST_REG_ADDR + REG_NUM * BLOCK_SIZE)

#define IDLE 0
#define BUSY 1
#define DONE 2

/* If output is set as 0, it is transfered to the CONV */
/* If output is set as 2, it is transfered to the POOL */
#define CONV_INPUT 0
#define CONV_FILTER 1
#define POOL_INPUT 2

#define LS   0
#define CONV 1
#define POOL 2

/* Default model */
#define act_row 1024
#define act_col 3
#define INPUT_LEN act_row * act_col
//#define INPUT_LEN 9
/* Filter */
#define FILTER1_NUM 32
#define FILTER2_NUM 64
#define FILTER3_NUM 32
#define FILTER4_NUM 64
#define FILTER_TOTAL_LEN (FILTER1_NUM*act_col + FILTER2_NUM*FILTER1_NUM + FILTER3_NUM*FILTER2_NUM + FILTER4_NUM*FILTER3_NUM)
/* {FILTER1_NUM*act_col, FILTER2_NUM*FILTER1_NUM, FILTER3_NUM*FILTER2_NUM, FILTER4_NUM*FILTER3_NUM}; Unit: Byte */
extern uint32_t filter_len[4]; 
extern uint8_t ext_filter[FILTER_TOTAL_LEN];
/* Output */
#define FILTER1_OUT_LEN act_row * FILTER1_NUM
#define FILTER2_OUT_LEN act_row * FILTER2_NUM
#define FILTER3_OUT_LEN act_row * FILTER3_NUM
#define FILTER4_OUT_LEN act_row * FILTER4_NUM
extern uint8_t ext_act[INPUT_LEN];
extern uint32_t input_dim[4];


#define cell(len)  (((len) + (BLOCK_SIZE) - 1) / (BLOCK_SIZE))

/* From main to load */
struct BlkCtrl_Bundle
{   
    uint8_t *ext_addr;
    uint32_t total_len;
    uint8_t IP_ID; 
};

/* From load to block (need to update ext_addr, int_addr, len in loop) */
struct Blk_Bundle
{   
    uint8_t *ext_addr;
    uint8_t *int_addr;
    uint32_t len;
};

struct Conv_Bundle
{   
    uint8_t *fil_addr;
    uint8_t *act_addr;
    uint8_t *out_addr;
    uint32_t fil_len;
    uint32_t act_len;
    uint32_t out_len;
};

struct IP_Bundle
{
    uint64_t IP_addr; /* This IP first addr */
    uint8_t IP_ID; /* The ID of this IP */
    uint8_t IP_state;  /* The state of this IP */
};

#endif