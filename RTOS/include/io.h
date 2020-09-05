#ifndef IO_H
#define IO_H

#include <stdint.h>


void out(volatile uint32_t* const, const uint32_t, const uint32_t, const uint32_t);
void clear(volatile uint32_t* const, const uint32_t, const uint32_t);
uint32_t in(volatile const uint32_t* const, uint32_t, const uint32_t);

#endif
