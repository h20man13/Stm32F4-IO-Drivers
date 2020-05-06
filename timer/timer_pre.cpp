#include "timer_pre.h"

const static pre_val* pll_point = (pre_val*)0x40023804;
const static pre_val* sys_point = (pre_val*)0x40023808;
const static pre_val* adc_point = (pre_val*)0x40012300;

inline pre_val Sample_Prescalar(pre_val (*func)()){
    return (*func)();
}
inline void Configure_Prescalar(void (*func)()){
  (*func)();
}

//sample funcs
pre_val PLLN(){
  return in((uint32_t*)pll_point, 9, 6);
}

pre_val PLLP(){
  return 1 << (in((uint32_t*)pll_point, 2, 16) + 1);
}

pre_val PLLM(){
  return in((uint32_t*)pll_point, 6, 0);
}

pre_val AHB1(){
  pre_val HPRE = in((uint32_t*)sys_point, 4, 4) - 0b1001;
  if(HPRE >= 4){
    HPRE++;
  }
  return 1 << HPRE;
}

pre_val APB1(){
  return 1 << (in((uint32_t*)sys_point, 3, 9) - 0b101);
}

pre_val APB2(){
  return 1 << (in((uint32_t*)sys_point, 3, 12) - 0b101);
}

pre_val ADC1(){
  return (in((uint32_t*)adc_point, 2, 16) + 1) * 2;
}

//other funcs

void PLLN(pre_val data){
  out((uint32_t*)pll_point, 9, 6, data);
}

void PLLP(pre_val data){
  out((uint32_t*)pll_point, 2, 16, data);
}

void PLLM(pre_val data){
  out((uint32_t*)pll_point, 6, 0, data);
}

void AHB1(pre_val data){
  out((uint32_t*)pll_point, 4, 4, data);
}

void APB1(pre_val data){
  out((uint32_t*)pll_point, 3, 9, data);
}

void APB2(pre_val data){
  out((uint32_t*)pll_point, 3, 12, data);
}

void ADC1(pre_val data){
  out((uint32_t*)adc_point, 2, 16, data);
}