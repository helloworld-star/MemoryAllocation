#ifndef INIT_H
#define INIT_H

#include "common.h"
#ifdef ENABLE_SIM_MODE
    #include "sim_common.h"
    #include "hardware.h"
    #include <assert.h>
#endif

struct Block
{
    uint8_t *int_addr;  // This block internal addr
    bool taken;     // Is taken by IP
};

struct IP
{
    uint8_t *IP_addr; // This IP first addr
    uint8_t IP_ID; // The ID of this IP
    uint8_t IP_state;  // The state of this IP
};

struct  Blockarray
{
    struct Block blocks[BLOCK_NUM];
    uint8_t block_free_num;
};

struct IP_block_list
{
    uint8_t DATA_TYPE;
    int8_t block_list[BLOCK_NUM]; // Record the used block ID of IP
    uint32_t res_len; // The len of resdual len (The other block takes the full BLOCK_SIZE of itself)
};

void Block_init(struct Blockarray *blockArray);

void IP_init(struct IP *IP_array);

void block_list_init(struct IP_block_list *taken_block, uint8_t DATA_TYPE);

#endif