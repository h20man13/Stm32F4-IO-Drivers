#include "timer_pre.h"

const static pre_val* pll_point = 0x40023804;
const static pre_val* sys_point = 0x40023808;

inline pre_val Sample_Prescalar(pre_val (*func)()){
    return (*func)();
}
inline void Configure_Prescalar(pre_void (*func)()){
  (*func)();
}

//sample funcs
pre_val pre_PLLN_get(){
  return in(pll_point, 9, 6);
}

pre_val pre_PLLP_get(){
  return 1 << (in(pll_point, 2, 16) + 1);
}

pre_val pre_PLLM_get(){
  return in(pll_point, 6, 0);
}

pre_val pre_AHB1_get(){
  pre_val HPRE = in(sys_point, 4, 4) - 0b1001;
  if(HPRE >= 4){
    HPRE++;
  }
  return 1 << HPRE;
}

pre_val pre_APB1_get(){
  return 1 << (in(sys_point, 3, 9) - 0b101);
}

pre_val pre_APB2_get(){
  return 1 << (in(sys_point, 3, 12) - 0b101);
}

//other funcs

void pre_PLLN_set(pre_val data){
  out(pll_point, 9, 6, data);
}

void pre_PLLP_set(pre_val data){
  out(pll_point, 2, 16, data);
}

void pre_PLLM_set(pre_val data){
  out(pll_point, 6, 0, data);
}

void pre_AHB1_set(pre_val data){
  out(pll_point, 4, 4, data);
}

void pre_APB1_set(pre_val data){
  out(pll_point, 3, 9, data);
}

void pre_APB2_set(pre_val data){
  out(pll_point, 3, 12, data);
}