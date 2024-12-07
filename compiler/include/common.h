#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define BLOCK_SIZE 4096
#define BLOCK_NUM 32
#define IP_NUM 2
#define CONV_LAYER 4

#define FIRST_BLOCK_ADDR 0x00000000
#define BLOCK_LAST_ADDRESS (FIRST_REG_ADDR + REG_NUM * BLOCK_SIZE - 1) 
#define FIRST_IP_ADDR (FIRST_REG_ADDR + REG_NUM * BLOCK_SIZE)

#define IDLE 0
#define BUSY 1
#define DONE 2

// If output is set as 0, it is transfered to the CONV
// If output is set as 2, it is transfered to the POOL
#define CONV_INPUT 0
#define CONV_FILTER 1
#define POOL_INPUT 2

#define LS   0
#define CONV 1
#define POOL 2

// Default model
#define act_row 1024
extern uint32_t filter_len[4];

#define cell(len)  (((len) + (BLOCK_SIZE) - 1) / (BLOCK_SIZE))

// From main to load
struct EXT2INT_Bundle
{   
    uint8_t *ext_addr;
    uint32_t total_len;
    uint8_t IP_ID; 
};

// From load to block (need to update ext_addr, int_addr, len in loop)
struct BLOCK_Bundle
{   
    uint8_t *ext_addr;
    uint8_t *int_addr;
    uint32_t len;
};

struct IP_Bundle
{
    uint64_t IP_addr; // This IP first addr
    uint8_t IP_ID; // The ID of this IP
    uint8_t IP_state;  // The state of this IP
};

#endif