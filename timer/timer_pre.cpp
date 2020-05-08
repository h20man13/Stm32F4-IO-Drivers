#include "timer_pre.h"

volatile static uint32_t* pll_point = (uint32_t*)0x40023804;
volatile static uint32_t* sys_point = (uint32_t*)0x40023808;
volatile static uint32_t* adc_point = (uint32_t*)0x40012300;

static pre pre_v;

const static double log_2 = log(2);

uint32_t Sample_Prescalar(uint32_t (pre::*func)()){
    return (pre_v.*func)();
}

void Configure_Prescalar(void (pre::*func)(uint32_t), uint32_t val){
  (pre_v.*func)(val);
}

//sample funcs
uint32_t pre::PLLN(){
  return in(pll_point, 9, 6);
}

uint32_t pre::PLLP(){
  return 1 << (in(pll_point, 2, 16) + 1);
}

uint32_t pre::PLLM(){
  return in(pll_point, 6, 0);
}

uint32_t pre::AHB1(){
  uint32_t HPRE = in(sys_point, 4, 4) - 0b111;
  if(HPRE >= 4){
    HPRE++;
  }
  return 1 << HPRE;
}

uint32_t pre::APB1(){
  return 1 << (in(sys_point, 3, 9) - 0b11);
}

uint32_t pre::APB2(){
  return 1 << (in(sys_point, 3, 12) - 0b11);
}

uint32_t pre::ADC1(){
  return (in(adc_point, 2, 16) + 1) * 2;
}

//other funcs

void pre::PLLN(uint32_t data){
  out(pll_point, 9, 6, data);
}

void pre::PLLP(uint32_t data){
  data = (log(data) - log_2) / log_2;
  out(pll_point, 2, 16, data);
}

void pre::PLLM(uint32_t data){
  out(pll_point, 6, 0, data);
}

void pre::AHB1(uint32_t data){
  if(data >= 64){
    data /= 2;
  }
  data = (log(data) + log(1 << 7)) / log_2;
  out(pll_point, 4, 4, data);
}

void pre::APB1(uint32_t data){
  data = (log(data) + log(1 << 3)) / log_2;
  out(pll_point, 3, 9, data);
}

void pre::APB2(uint32_t data){
  data = log(data * (1 << 3)) / log_2;
  out(pll_point, 3, 12, data);
}

void pre::ADC1(uint32_t data){
    data = data / 2 - 1;
    if(data >= 0 && data <= 3){
      out(adc_point, 2, 16, data);
    }
    else{
      //print message saying data is an invalid value
    }
}