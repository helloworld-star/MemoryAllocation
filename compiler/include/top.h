#ifndef TOP_H
#define TOP_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define BLOCK_SIZE 4096
#define BLOCK_NUM 32
#define IP_NUM 8

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

#define cell(len)  (((len) + (BLOCK_SIZE) - 1) / (BLOCK_SIZE))

#endif