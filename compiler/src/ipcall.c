#include "ipcall.h"


void read_IP_state(struct IP *IPArray)
{
    #ifdef ENABLE_SIM_MODE
    for(uint8_t i = 0; i < IP_NUM; i++)
        IPArray[i].IP_state = IP_state[i];
    #else
    /* Read the state of IP from IP_addr */
    for(uint8_t i = 0; i < IP_NUM; i++)
        IPArray[i].IP_state = IPArray[i].IP_addr;
    #endif
    return;
}

bool CheckBoundary(struct Blockarray *blockArray, uint8_t block_need)
{
    //printf("block_free_num: %d\n", blockArray->block_free_num);
    if(blockArray->block_free_num < block_need)
    {
        printf("No enough space for loading\n");
        return false;
    }

    return true;
}

void load(struct Blockarray *blockArray, struct IP_block_list *load_list, struct BlkCtrl_Bundle blkctrl_bundle)
{
    /* The number of blocks needed */
    int8_t block_need = cell((float)blkctrl_bundle.total_len);

    bool enough = CheckBoundary(blockArray, block_need);
    if (enough == false)
    {
        // store();
        assert(0);
        return;
    }

    /* EXT2INT bunble tansfer to Blk_Bundle (add int_addr) */
    struct Blk_Bundle blk_bundle;
    blk_bundle.ext_addr = blkctrl_bundle.ext_addr;

    uint32_t res_len = blkctrl_bundle.total_len % BLOCK_SIZE;
    blk_bundle.len = block_need == 1 ? res_len : BLOCK_SIZE;
    load_list->res_len = res_len;

    blockArray->block_free_num -= block_need;

    uint8_t block_count = 0;
    uint8_t list_count = 0;

    for(block_count = 0; (block_count < BLOCK_NUM); block_count++)
    {
        if(blockArray->blocks[block_count].taken == false)
        {
            blk_bundle.int_addr = blockArray->blocks[block_count].int_addr;
            // printf("Block int_addr: %ld\n", (uint64_t)(blk_bundle.int_addr));

            // 汇编 将数据从片外读入片内
            #ifdef ENABLE_SIM_MODE
                printf("Sim load!\n");
                sim_load(blk_bundle);
            #else
                
            #endif

            /* Set blockArray state */
            blockArray->blocks[block_count].taken = true;
            /* Record the Block ID */
            load_list->block_list[list_count] = block_count;

            list_count++;
            block_need--;
            if (block_need == 0)
                break;
            /* After a block loading, update the state. */
            blk_bundle.ext_addr = blk_bundle.ext_addr + BLOCK_SIZE;
            /* res_len > 0: last block loading res_len */
            /* res_len == 0: last block loading BLOCK_SIZE (res_len =0, No data will be loaded) */
            blk_bundle.len = (block_need == 1 && res_len != 0) ? res_len : BLOCK_SIZE;
        }
    }

    return;
}

void conv(struct Blockarray *blockArray, struct IP_block_list *act_list, struct IP_block_list *filter_list, uint32_t output_len)
{
    /* The number of blocks needed for output */
    int8_t block_need = cell((float)output_len);

    bool enough = CheckBoundary(blockArray, block_need);
    if (enough == false)
    {
        // store();
        assert(0);
        return;
    }

    blockArray->block_free_num -= block_need;

    /* Need to update. */
    // uint32_t res_len = output_len % BLOCK_SIZE; 

    struct Conv_Bundle conv_bundle;
    conv_bundle.act_len = act_list->res_len;
    conv_bundle.fil_len = filter_list->res_len;
    conv_bundle.act_addr = blockArray->blocks[act_list->block_list[0]].int_addr;
    conv_bundle.fil_addr = blockArray->blocks[filter_list->block_list[0]].int_addr;

    uint32_t block_count;
    for(block_count = 0; (block_count < BLOCK_NUM); block_count++)
    {
        if(blockArray->blocks[block_count].taken == false)
        {
            conv_bundle.out_addr = blockArray->blocks[block_count].int_addr;
            break;
        }
    }

    /* Need to update. If the output needs more blocks, maybe the number act and filter should be spilt to make the output can be saved in one block. */
    #ifdef ENABLE_SIM_MODE
        printf("Sim conv!\n");
        sim_conv(conv_bundle);
    #else
        
    #endif

    return;
}