// #include "common.h"
// #include "init.h"

// int main()
// {
//     struct BlockArray blockarray;
//     struct IP IPArray[IP_NUM];

//     Block_init(&blockarray);
//     IP_init(&IPArray);

//     struct IP_block_list input_block_list;
//     struct IP_block_list filter_block_list;

//     // Input only load once, in rest cycles, it is used as output (next model's input)
//     block_list_init(&input_block_list, CONV_INPUT);
//     block_list_init(&filter_block_list, CONV_FILTER);

//     // 速度 谁等谁
//     bool start_load = false;
//     uint8_t conv_count = 0;
//     while(1)
//     {
//         read_IP_state(&IPArray);
        
//         if(start_load == true && IPArray[LS].IP_state == IDLE)
//         {
//             CheckBoundary(&blockarray, 1024);
//         }



//     }

//     return 0;
// }