#include "init.h"

void Block_init(struct BlockArray *blockarray)
{
	blockarray->free_start = 0;
	blockarray->free_end = BLOCK_NUM-1;
	blockarray->free_num = BLOCK_NUM;
    return;
}

void IP_init(struct IP *IP_array)
{
    uint8_t i;
    for(i = 0; i < IP_NUM; i++)
    {
        IP_array[i].IP_state = IDLE;
        IP_array[i].IP_addr = 0;
    }

    return;
}


