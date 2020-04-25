#include "io.h"

void out(uint32_t* addr, uint32_t size, uint32_t shift, uint32_t data){
  if(data < 1 << size){
    clear(addr, size, shift);
    *addr |= (data << shift);
  }
}

void clear(uint32_t* addr, uint32_t size, uint32_t shift){
  uint32_t clear = (1 << size) - 1;
  clear = ~(clear << shift);
  *addr &= clear;
}

uint32_t in(volatile uint32_t* addr, uint32_t size, uint32_t shift){
  uint32_t save = (1 << size) - 1;
  return (*addr >> shift) & save;
}
