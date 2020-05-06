#include <stdint.h>
#include <stdbool.h>

#include "gpio.h"
#include "io.h"

static uint32_t counts[5] = {0,0,0,0,0};

//sample gpio fuctions
GPIO::GPIO(const GPIO_Addr addr, const GPIO_Pin p){
  uint32_t save = (addr - 0x40020000)/0x400;
  if(counts[addr - 0x4] == 0){
    Configure_AHB1_ENR(save, on);
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
    uint32_t save = (MODER - 0x40020000)/0x400;
    clear(MODER, 2, num);
    clear(OTYPER, 1, PIN_NUM);
    clear(OSPEEDR, 2, num);
    clear(PUPDR, 2, num);
    clear(ODR, 1, PIN_NUM);
    counts[save]--;
    if(counts[save] == 0){
      //Configure_AHB1_ENR(save, off);
    }
}
//Create mode functions (mode == void)
void GPIO::Configure_MODER(MODER value){
  out(MODER, 2, PIN_NUM * 2, value);
}
void GPIO::Configure_OTYPER(OTYPER value){
  out(OTYPER, 1, PIN_NUM, value);
}
void GPIO::Configure_OSPEEDR(GPIO::OSPEEDR value){
  out(OSPEEDR, 2, PIN_NUM * 2, value);
}
void GPIO::Configure_PUPDR(GPIO::PUPDR value){
  out(PUPDR, 2, PIN_NUM * 2, value);
}
void GPIO::Configure_ODR(STATE value){
  out(ODR, 1, PIN_NUM, value);
}
bool GPIO::Sample_IDR(){
  return in(IDR, 1, PIN_NUM);
}