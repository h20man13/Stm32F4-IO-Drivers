#include "io.h"

void out(uint32_t* addr, uint32_t size, uint32_t shift, uint32_t data){
  uint32_t clear = (1 << size) - 1;
  clear = ~(clear << shift);
  *addr &= clear;
  *addr |= (data << shift);
}

uint32_t in(uint32_t* addr, uint32_t size, uint32_t shift){
  uint32_t save = (1 << size) - 1;
  return (*addr >> shift) & save;
}
