#include "timer_pre.h"

const static pre_val* pll_point = 0x40023804;
const static pre_val* sys_point = 0x40023808;

inline pre_val Sample_Prescalar(pre_val (*func)()){
    return (*func)();
}

pre_val PLLN(){
  return (*pll_point >> 6) & 0b111111111;
}

pre_val PLLP(){
  return 1 << (((*pll_point >> 16) & 0b11) + 1);
}

pre_val PLLM(){
  return *pll_point & 0b111111;
}

pre_val AHB1(){
  pre_val HPRE = (((*sys_point >> 4) & 0b1111) - 0b1000) + 1;
  if(HPRE >= 4){
    HPRE++;
  }
  return 1 << HPRE;
}

pre_val APB1(){
  pre_val PPRE1 = ((((*sys_point >> 9) & 0b111) - 0b100) + 1);
  if(PPRE1 < 0){
    PPRE1 = 0;
  }
  return 1 << PPRE1;
}

pre_val APB2(){
  pre_val PPRE2 = (((*sys_point >> 12) & 0b111) - 0b100) + 1;
  if(PPRE2 < 0){
    PPRE2 = 0;
  }
  return 1 << PPRE2;
}