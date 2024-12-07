#include "common.h"
#include "init.h"
#include "ipcall.h"
#ifdef ENABLE_SIM_MODE
    #include "sim_common.h"
    #include "hardware.h"
#endif

uint32_t filter_len[4] = {32*act_row, 64*act_row, 32*act_row, 64*act_row};

int main()
{
    struct Blockarray blockArray;
    struct IP IPArray[IP_NUM];

    #ifdef ENABLE_SIM_MODE
        printf("In simulation mode!\n");
        init_sim();
        printf("%d\n", ext_filter[100]);
    #endif

    Block_init(&blockArray);
    #ifdef ENABLE_SIM_MODE
        for (uint8_t i = 0; i < BLOCK_NUM; i++)
        {
            // printf("block_addr: %ld\n",  (uint64_t)(blockArray.blocks[i].int_addr));
            // printf("int_addr: %ld\n",  (uint64_t)(&int_mem[i * BLOCK_SIZE]));
            Assert((uint64_t)(blockArray.blocks[i].int_addr) == (uint64_t)(&int_mem[i * BLOCK_SIZE]), "In init!");
        }
    #endif
    IP_init(IPArray);

    struct IP_block_list input_block_list;
    struct IP_block_list filter_block_list;

    // Input only load once, in rest cycles, it is used as output (next model's input)
    block_list_init(&input_block_list, CONV_INPUT);
    block_list_init(&filter_block_list, CONV_FILTER);

    // 速度 谁等谁
    // bool start_load = false;
    // uint8_t conv_count = 0;

    while(1)
    {
        struct EXT2INT_Bundle input_bundle;
        read_IP_state(IPArray);
        if (IPArray[LS].IP_state == IDLE)
        {
            #ifdef ENABLE_SIM_MODE
                input_bundle.ext_addr = &ext_filter[0];
            #else
            #endif
            input_bundle.IP_ID = LS;
            input_bundle.total_len = filter_len[0];
            load(&blockArray, &input_block_list, input_bundle);
            #ifdef ENABLE_SIM_MODE
                for (uint32_t i = 0; i < filter_len[0]; i++)
                {
                    // printf("block_addr: %ld\n",  (uint64_t)(ext_filter[i]));
                    // printf("int_filter: %ld\n",  (uint64_t)(int_mem[i]));
                    Assert((uint64_t)(ext_filter[i]) == (uint64_t)(int_mem[i]), "In load!");
                }
            #endif
            break;
        }
    }

    // while(1)
    // {
    //     read_IP_state(IPArray);
        
    //     if(start_load == true && IPArray[LS].IP_state == IDLE)
    //     {
    //         CheckBoundary(&blockArray, 1024);
    //         // load();
    //         start_load = false;
    //     }

    //     if(start_load == false && IPArray[CONV].IP_state == IDLE)
    //     {
    //         // conv();
    //         conv_count++;
    //         start_load = true;
    //     }

    //     if(conv_count == CONV_LAYER)
    //     {
    //         // pool();
    //         conv_count = 0;
    //     }
    //     printf("Success\n");
    //     break;
    // }

    return 0;
}