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
    uint8_t *int_addr;  /* This block internal addr */
    bool taken;     /* Is taken by IP */
};

/* Free Start = Taken End; Free End == Taken Start */
/* Free: Block Num - |Free Start - Free End| */
/* Taken: Block Num - |Free End - Free Start| */
struct BlockArray
{
    uint8_t free_start;
    uint8_t free_num;
};

struct IP
{
    uint8_t *IP_addr; /* This IP first addr */
    uint8_t IP_ID; /* The ID of this IP */
    uint8_t IP_state;  /* The state of this IP */
};

struct IP_block_list
{
	uint8_t block_start;
	uint8_t block_num; /* For deleting */
    uint32_t len;
};

void Block_init(struct BlockArray *blockarray);

void IP_init(struct IP *IP_array);

#endif
