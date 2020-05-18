#include "io.h"

void out(volatile uint32_t* const addr, const uint32_t size, const uint32_t shift, const uint32_t data){
  if(data < 1 << size){
    clear(addr, size, shift);
    *addr |= (data << shift);
  }
}

void clear(volatile uint32_t* const addr, const uint32_t size, const uint32_t shift){
  uint32_t clear = (1 << size) - 1;
  clear = ~(clear << shift);
  *addr &= clear;
}

uint32_t in(volatile const uint32_t* const addr, const uint32_t size, const uint32_t shift){
  uint32_t save = (1 << size) - 1;
  return (*addr >> shift) & save;
}