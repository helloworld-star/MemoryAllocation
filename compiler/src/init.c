#include "init.h"

void Block_init(struct Blockarray *blockArray)
{
    uint8_t i;
    for(i = 0; i < BLOCK_NUM; i++)
    {   
        #ifdef ENABLE_SIM_MODE
            blockArray->blocks[i].int_addr = &int_mem[i * BLOCK_SIZE];
        #else
            blockArray->blocks[i].int_addr = 0;
        #endif
        blockArray->blocks[i].taken = false;
    }

    blockArray->block_free_num = BLOCK_NUM;
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

void block_list_init(struct IP_block_list *taken_block, uint8_t DATA_TYPE)
{
    taken_block->DATA_TYPE = DATA_TYPE;
    taken_block->res_len = 0;

    uint8_t i;
    for(i = 0; i < BLOCK_NUM; i++)
    {
        taken_block->block_list[i] = -1;
    }

    return;
}