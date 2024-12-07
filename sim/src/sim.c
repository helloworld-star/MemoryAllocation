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