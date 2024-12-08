#ifndef SIM_COMMON_H
#define SIM_COMMON_H

#include "common.h"

#define fil_num 192

void Assert(uint32_t judge, char *str);
void write_to_file(uint8_t *data_addr, uint64_t data_len, uint32_t values_per_line, const char *file_name);

#endif