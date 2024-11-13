#include "ipcall.h"

void read_IP_state(struct IP *IPArray)
{
    // Read the state of IP from IP_addr
    for (int i = 0; i < IP_NUM; i++)
        IPArray[i].IP_state = IPArray[i].IP_addr;

    return;
}

bool CheckBoundary(struct Blockarray *block_array, uint32_t len)
{
    uint8_t block_need = cell(len);

    if (block_array->block_free_num < block_need)
    {
        printf("No enough space for loading\n");
        return false;
    }

    return true;
}


void load(struct Blockarray *block_array, struct IP_block_list *load_list, uint32_t ext_addr, uint32_t len, uint8_t IP_ID)
{
    // The number of blocks needed
    uint8_t block_need = cell((float)len / (float)BLOCK_SIZE);
    load_list->res_len = len % BLOCK_SIZE;

    block_array->block_free_num -= block_need;

    uint8_t block_count = 0;
    uint8_t list_count = 0;
    for(block_count = 0; (block_count < BLOCK_NUM) && block_need == 0; block_count++)
    {
        if(block_array->blocks[block_count].taken == false)
        {
            // 汇编 将数据从片外读入片内
            #ifdef SIM
                //sim_load();
            #endif
            // Set block_array state
            block_array->blocks[block_count].taken = true;
            // Record the Block ID
            load_list->block_list[list_count] = block_count;

            list_count++;
            block_need--;
        }
    }

    return;
}

void conv(struct Blockarray *block_array, struct IP *IPArray, uint8_t IP_ID, uint32_t act_ID, uint32_t fil_ID, uint32_t out_addr)
{
    // 读还是自己设置
    IPArray[IP_ID].IP_state = BUSY;

    // 汇编 写数据
    // block_array[act_ID].addr;
    // block_array[fil_ID].addr;

    // 汇编完后可以马上置为false 设为output addr吗
    block_array->blocks[act_ID].taken = false;
    block_array->blocks[fil_ID].taken = false;

    // 输出数据长度是可读的还是自行计算

    return;
}