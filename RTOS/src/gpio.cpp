#include <stdint.h>
#include <stdbool.h>

#include "gpio.h"
#include "io.h"
#include "timer_enable.h"

uint32_t GPIO::counts[5]{0,0,0,0,0};

//sample gpio fuctions
GPIO::GPIO(const GPIO_Addr addr, const GPIO_Pin p){
  uint32_t save = (addr - 0x40020000)/0x400;
  if(counts[save] == 0){
    enable_timer(addr);
  }
  MODER = (uint32_t*)addr;
  OSPEEDR = (uint32_t*)(addr + 0x08);
  PUPDR = (uint32_t*)(addr + 0x0C);
  IDR = (volatile uint32_t*)(addr + 0x10);
  OTYPER = (uint32_t*)(addr + 0x04);
  ODR = (uint32_t*)(addr + 0x14);
  PIN_NUM = p;
  counts[save]++;
}

GPIO::~GPIO(){
    uint32_t num = PIN_NUM * 2;
    uint32_t save = (MODER - (uint32_t*)0x40020000)/0x400;
    GPIO_Addr MODR = (GPIO_Addr)(uint32_t)MODER;
    clear(MODER, 2, num);
    clear(OTYPER, 1, PIN_NUM);
    clear(OSPEEDR, 2, num);
    clear(PUPDR, 2, num);
    clear(ODR, 1, PIN_NUM);
    counts[save]--;
    if(counts[save] == 0){
      disable_timer(MODR);
    }
}
//Create mode functions (mode == void)
void GPIO::Configure_MODER(MODER_vals value){
  out(MODER, 2, PIN_NUM * 2, value);
}
void GPIO::Configure_OTYPER(OTYPER_vals value){
  out(OTYPER, 1, PIN_NUM, value);
}
void GPIO::Configure_OSPEEDR(OSPEEDR_vals value){
  out(OSPEEDR, 2, PIN_NUM * 2, value);
}
void GPIO::Configure_PUPDR(PUPDR_vals value){
  out(PUPDR, 2, PIN_NUM * 2, value);
}
void GPIO::Configure_ODR(STATE value){
  out(ODR, 1, PIN_NUM, value);
}
bool GPIO::Sample_IDR(){
  return in(IDR, 1, PIN_NUM);
}
