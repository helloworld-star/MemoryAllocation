#include "top.h"
#include "init.h"
#include "ipcall.h"
#include "sim.h"

int main()
{
    struct Blockarray blockArray;
    struct IP IPArray[IP_NUM];

    init_sim();

    printf("%d\n", external_filter[100]);

    Block_init(&blockArray);
    IP_init(IPArray);

    struct IP_block_list input_block_list;
    struct IP_block_list filter_block_list;

    // Input only load once, in rest cycles, it is used as output (next model's input)
    block_list_init(&input_block_list, CONV_INPUT);
    block_list_init(&filter_block_list, CONV_FILTER);

    // 速度 谁等谁
    bool start_load = false;
    uint8_t conv_count = 0;
    //while(1)
    {
        read_IP_state(IPArray);

        // load(&blockArray, &input_block_list, &filter_block_list, &conv_count);

        
        if (start_load == true && IPArray[LS].IP_state == IDLE)
        {
            CheckBoundary(&blockArray, 1024);
            start_load = false;
        }

        if (start_load == false && IPArray[CONV].IP_state == IDLE)
        {
            
        }
        printf("Success\n");
    }

    return 0;
}