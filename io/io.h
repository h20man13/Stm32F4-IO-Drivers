#ifndef IO_H
#define IO_H

#include <stdint.h>

void out(void*, uint32_t, uint32_t, uint32_t);
void clear(void*, uint32_t, uint32_t);
uint32_t in(void*, uint32_t, uint32_t);

#endif
