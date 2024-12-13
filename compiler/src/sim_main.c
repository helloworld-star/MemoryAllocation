#include "common.h"
#include "init.h"
#include "ipcall.h"
#ifdef ENABLE_SIM_MODE
    #include "sim_common.h"
    #include "hardware.h"
#endif

uint32_t input_dim[4] = {act_col, FILTER1_NUM, FILTER2_NUM, FILTER3_NUM}; /* Col num */
uint32_t filter_len[4] = {FILTER1_NUM*act_col, FILTER2_NUM*FILTER1_NUM, FILTER3_NUM*FILTER2_NUM, FILTER4_NUM*FILTER3_NUM};
uint32_t output_len[4] = {FILTER1_OUT_LEN, FILTER2_OUT_LEN, FILTER3_OUT_LEN, FILTER4_OUT_LEN};

int main()
{
    struct BlockArray blockarray;
    struct IP IPArray[IP_NUM];

    #ifdef ENABLE_SIM_MODE
        printf("In simulation mode!\n");
        init_sim();
    #endif

    Block_init(&blockarray);
    IP_init(IPArray);

    struct IP_block_list input_block_list;
    struct IP_block_list filter_block_list;

    /* 速度 谁等谁 */
    bool start_load = true;
    uint8_t conv_count = 0;

    struct BlkCtrl_Bundle input_bundle;
    input_bundle.IP_ID = LS;
    input_bundle.total_len = INPUT_LEN;

    while(1)
    {
        read_IP_state(IPArray);
        if (IPArray[LS].IP_state == IDLE)
        {
            #ifdef ENABLE_SIM_MODE
                input_bundle.ext_addr = &ext_act[0];
            #else
            #endif
            load(&blockarray, &input_block_list, input_bundle);

            #ifdef ENABLE_SIM_MODE
                for (uint32_t i = 0; i < INPUT_LEN; i++)
                {
                    // printf("ext_act: %ld\n",  (uint64_t)(ext_act[i]));
                    // printf("int_filter: %ld\n",  (uint64_t)(BLOCK(0)[i]));
                    Assert((uint64_t)(ext_act[i]) == (uint64_t)(BLOCK(0)[i]), "In load!");
                }
            #endif
            break;
        }
    }

    while(1)
    {
        read_IP_state(IPArray);
        
        if(start_load == true && IPArray[LS].IP_state == IDLE)
        {
            input_bundle.total_len = filter_len[0];
            input_bundle.ext_addr = &ext_filter[0];
            load(&blockarray, &filter_block_list, input_bundle);

            #ifdef ENABLE_SIM_MODE
                for (uint32_t i = 0; i < filter_len[0]; i++)
                {
                    // printf("ext_filter: %ld\n",  (uint64_t)(ext_filter[i]));
                    // printf("int_filter: %ld\n",  (uint64_t)(BLOCK(1)[i]));
                    Assert((uint64_t)(ext_filter[i]) == (uint64_t)(BLOCK(1)[i]), "In load!");
                }
            #endif

            start_load = false;
        }

        if(start_load == false && IPArray[CONV].IP_state == IDLE)
        {
            conv(&blockarray, &input_block_list, &filter_block_list, output_len[0]);
            conv_count++;
            start_load = true;
        }

        printf("Success\n");
        break;

        // if(conv_count == CONV_LAYER)
        // {
        //     // pool();
        //     conv_count = 0;
        // }
    }

    write_to_file(BLOCK(0), INPUT_LEN, 3, "./test/Input.txt");
    write_to_file(BLOCK(1), filter_len[0], 3, "./test/Filter.txt");
    write_to_file(BLOCK(2), FILTER1_OUT_LEN, 32, "./test/Output.txt");

    return 0;
}