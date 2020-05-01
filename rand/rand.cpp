#include <stdint.h>
#include <stdbool.h>

#include "rand.h"
static uint32_t seed_v;
static bool ok = false;

void seed(uint32_t s){
  seed_v = s;
  ok = true;
}

uint32_t sudo_randomUint32(){
  if(ok){
    seed_v = (64 * seed_v + 128) % 0xffffffff;
    return seed_v;
  }
  else{
    //eventually print statement like seed was not determined and maybe choose a random seed
    return -1;
  }
}
