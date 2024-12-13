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

bool CheckBoundary(struct BlockArray *blockarray, uint8_t block_need)
{
    //printf("free_num: %d\n", blockarray->free_num);
    if(blockarray->free_num < block_need)
    {
        printf("No enough space for loading\n");
        return false;
    }

    return true;
}

void load(struct BlockArray *blockarray, struct IP_block_list *load_list, struct BlkCtrl_Bundle blkctrl_bundle)
{
    /* The number of blocks needed */
    int8_t block_need = cell((float)blkctrl_bundle.total_len);

    bool enough = CheckBoundary(blockarray, block_need);
    if (enough == false)
    {
        // store();
        assert(0);
        return;
    }

    /* EXT2INT bunble tansfer to Blk_Bundle (add int_addr) */
    struct Blk_Bundle blk_bundle;
    blk_bundle.ext_addr = blkctrl_bundle.ext_addr;
	blk_bundle.int_addr = BLOCK(blockarray->free_start);
	blk_bundle.len = blkctrl_bundle.total_len;

    #ifdef ENABLE_SIM_MODE
    	printf("Sim load!\n");
        sim_load(blk_bundle);
    #else
                
    #endif

	/* Record start and num for deleting after conv */
	load_list->block_start = blockarray->free_start;
	load_list->block_num = block_need; 
    load_list->len = blkctrl_bundle.total_len; 

	/* Update blockarray state */
	blockarray->free_start += block_need;
	blockarray->free_start = (blockarray->free_start > (BLOCK_NUM-1)) ? (blockarray->free_start - BLOCK_NUM) : blockarray->free_start;
    blockarray->free_num -= block_need;

    return;
}

void conv(struct BlockArray *blockarray, struct IP_block_list *act_list, struct IP_block_list *filter_list, uint32_t output_len)
{
    /* The number of blocks needed for output */
    int8_t block_need = cell((float)output_len);

    bool enough = CheckBoundary(blockarray, block_need);
    if (enough == false)
    {
        // store();
        assert(0);
        return;
    }

    /* Need to update. */
    struct Conv_Bundle conv_bundle;
    conv_bundle.act_len = act_list->len;
    conv_bundle.fil_len = filter_list->len;
    conv_bundle.act_addr = BLOCK(act_list->block_start);
    conv_bundle.fil_addr = BLOCK(filter_list->block_start);

    conv_bundle.out_addr = BLOCK(blockarray->free_start);

    /* Update blockarray state */
    blockarray->free_start += block_need;
	blockarray->free_start = (blockarray->free_start > (BLOCK_NUM-1)) ? (blockarray->free_start - BLOCK_NUM) : blockarray->free_start;
    blockarray->free_num -= block_need;

    /* Need to update. If the output needs more blocks, maybe the number act and filter should be spilt to make the output can be saved in one block. */
    #ifdef ENABLE_SIM_MODE
        printf("Sim conv!\n");
        sim_conv(conv_bundle);
    #else
        
    #endif

    return;
}
