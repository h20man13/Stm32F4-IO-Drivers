#include <stdint.h>
#include <stdbool.h>

#include "gpio.h"
#include "io.h"

//sample gpio fuctions
void Init_GPIO(GPIO_Struct* const gstruct, const GPIO addr, const GPIO_Pin p){
  Configure_AHB1_ENR((ENABLE_AHB1)(((uint32_t)addr - 0x40020000)/0x400), on);
  gstruct -> MODER = (uint32_t*)addr;
  gstruct -> OSPEEDR = (uint32_t*)(addr + 0x08);
  gstruct -> PUPDR = (uint32_t*)(addr + 0x0C);
  gstruct -> IDR = (volatile uint32_t*)(addr + 0x10);
  gstruct -> OTYPER = (uint32_t*)(addr + 0x04);
  gstruct -> ODR = (uint32_t*)(addr + 0x14);
  gstruct -> PIN_NUM = p;
}

void Disable_GPIO(GPIO_Struct* base){
    uint32_t num = base -> PIN_NUM * 2;
    clear(base -> MODER, 2, num);
    clear(base -> OTYPER, 1, base -> PIN_NUM);
    clear(base -> OSPEEDR, 2, num);
    clear(base -> PUPDR, 2, num);
    clear(base -> ODR, 1, base -> PIN_NUM);
    Configure_AHB1_ENR((ENABLE_AHB1)(((uint32_t)base -> MODER - 40020000)/0x400), off);
}
//Create mode functions (mode == void)
void Configure_MODER(GPIO_Struct* const base, const MODER value){
  out(base -> MODER, 2, base -> PIN_NUM * 2, value);
}
void Configure_OTYPER(GPIO_Struct* const base, const OTYPER value){
  out(base -> OTYPER, 1, base -> PIN_NUM, value);
}
void Configure_OSPEEDR(GPIO_Struct* const base, const OSPEEDR value){
  out(base -> OSPEEDR, 2, base -> PIN_NUM * 2, value);
}
void Configure_PUPDR(GPIO_Struct* const base, const PUPDR value){
  out(base -> PUPDR, 2, base -> PIN_NUM * 2, value);
}
void Configure_ODR(GPIO_Struct* const base, const STATE value){
  out(base -> ODR, 1, base -> PIN_NUM, value);
}
bool Sample_IDR(GPIO_Struct* const base){
  return in(base -> IDR, 1, base -> PIN_NUM);
}
