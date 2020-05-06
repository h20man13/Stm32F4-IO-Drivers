#ifndef IO_H
#define IO_H

#include <stdint.h>

void out(uint32_t*, uint32_t, uint32_t, uint32_t);
void clear(uint32_t*, uint32_t, uint32_t);
uint32_t in(volatile uint32_t*, uint32_t, uint32_t);

#endif
