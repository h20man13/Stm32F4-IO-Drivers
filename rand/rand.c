#include "rand.h"
static uint32_t seed;
static bool ok = false;

void seed(uint32_t s){
  seed = s;
  ok = true;
}

uint32_t sudo_randomUint32(){
  if(ok){
    seed = (64 * seed + 128) % 0xffffffff;
    return seed;
  }
  else{
    //eventually print statement like seed was not determined and maybe choose a random seed
    return -1;
  }
}
