#include "sim_common.h"
#include "assert.h"

void Assert(uint32_t judge, char *str)
{
    if (!judge)
    {
        printf("Assert failed: %s\n", str);
        assert(0);
    }
}

void write_to_file(uint8_t *data_addr, uint64_t data_len, uint32_t values_per_line, const char *file_name) 
{
    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        printf("Error opening file: %s\n", file_name);
        return;
    }

    for (uint64_t i = 0; i < data_len; i += values_per_line)
    {
        for (uint32_t j = 0; j < values_per_line; j++)
        {
            if ((i + j) < data_len)
            { 
                fprintf(file, "%u ", data_addr[i + j]);
            }
        }
        fprintf(file, "\n"); 
    }

    fclose(file);
    printf("Data successfully written to file: %s\n", file_name);
}
