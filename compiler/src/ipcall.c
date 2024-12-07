#include "ipcall.h"


void read_IP_state(struct IP *IPArray)
{
    #ifdef ENABLE_SIM_MODE
    for(uint8_t i = 0; i < IP_NUM; i++)
        IPArray[i].IP_state = IP_state[i];
    #else
    // Read the state of IP from IP_addr
    for(uint8_t i = 0; i < IP_NUM; i++)
        IPArray[i].IP_state = IPArray[i].IP_addr;
    #endif
    return;
}

bool CheckBoundary(struct Blockarray *blockArray, uint32_t block_need)
{
    if(blockArray->block_free_num < block_need)
    {
        printf("No enough space for loading\n");
        return false;
    }

    return true;
}

void load(struct Blockarray *blockArray, struct IP_block_list *load_list, struct EXT2INT_Bundle mem_bundle)
{
    // The number of blocks needed
    uint8_t block_need = cell((float)mem_bundle.total_len / (float)BLOCK_SIZE);
    bool enough = CheckBoundary(blockArray, block_need);
    if (enough == false)
    {
        // store();
        assert(0);
        return;
    }

    // EXT2INT bunble tansfer to BLOCK_Bundle (add int_addr)
    struct BLOCK_Bundle block_bundle;
    block_bundle.ext_addr = mem_bundle.ext_addr;
    block_bundle.len = BLOCK_SIZE;

    uint32_t res_len = mem_bundle.total_len % BLOCK_SIZE;
    load_list->res_len = res_len;

    blockArray->block_free_num -= block_need;

    uint8_t block_count = 0;
    uint8_t list_count = 0;

    for(block_count = 0; (block_count < BLOCK_NUM) || block_need == 0; block_count++)
    {
        if(blockArray->blocks[block_count].taken == false)
        {
            
            block_bundle.int_addr = blockArray->blocks[block_count].int_addr;
            // 汇编 将数据从片外读入片内
            #ifdef ENABLE_SIM_MODE
                printf("Sim load!\n");
                sim_load(block_bundle);
            #else
                
            #endif

            // Set blockArray state
            blockArray->blocks[block_count].taken = true;
            // Record the Block ID
            load_list->block_list[list_count] = block_count;

            list_count++;
            block_need--;

            // After a block loading, update the state.
            block_bundle.ext_addr = mem_bundle.ext_addr + BLOCK_SIZE;
            block_bundle.len = block_need == 1 ? res_len : BLOCK_SIZE;
        }
    }

    return;
}

void conv(struct Blockarray *blockArray, struct IP *IPArray, uint8_t IP_ID, uint32_t act_ID, uint32_t fil_ID, uint32_t out_addr)
{
    // IPArray[IP_ID].IP_state = BUSY;

    // 汇编 写数据
    // input_block_list.
    // blockArray[act_ID].addr;
    // blockArray[fil_ID].addr;

    blockArray->blocks[act_ID].taken = false;
    blockArray->blocks[fil_ID].taken = false;

    return;
}