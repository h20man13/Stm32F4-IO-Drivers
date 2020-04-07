#include <stdint.h>
#include <stdbool.h>

#include "gpio.h"

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
    *base -> MODER &= ~(0b11 << (base -> PIN_NUM * 2));
    *base -> OTYPER &= ~(1 << base -> PIN_NUM);
    *base -> OSPEEDR &= ~(0b11 << (base -> PIN_NUM * 2));
    *base -> PUPDR &= ~(0b11 << (base -> PIN_NUM * 2));
    *base -> ODR &= ~(1 << base -> PIN_NUM);
    Configure_AHB1_ENR((ENABLE_AHB1)(((uint32_t)base -> MODER - 40020000)/0x400), off);
}
//Create mode functions (mode == void)
void Configure_MODER(GPIO_Struct* const base, const MODER value){
  *base -> MODER &= ~(0b11 << (base -> PIN_NUM * 2));
  *base -> MODER |= (value << (base -> PIN_NUM * 2));
}
void Configure_OTYPER(GPIO_Struct* const base, const OTYPER value){
  *base -> OTYPER &= ~(1 << base -> PIN_NUM);
  *base -> OTYPER |= (value << base -> PIN_NUM);
}
void Configure_OSPEEDR(GPIO_Struct* const base, const OSPEEDR value){
  *base -> OSPEEDR &= ~(0b11 << (base -> PIN_NUM * 2));
  *base -> OSPEEDR |= (value << (base -> PIN_NUM * 2));
}
void Configure_PUPDR(GPIO_Struct* const base, const PUPDR value){
  *base -> PUPDR &= ~(0b11 << (base -> PIN_NUM * 2));
  *base -> PUPDR |= (value << (base -> PIN_NUM * 2));
}
void Configure_ODR(GPIO_Struct* const base, const STATE value){
  *base -> ODR &= ~(1 << base -> PIN_NUM);
  *base -> ODR |= (value << base -> PIN_NUM);
}
bool Sample_IDR(GPIO_Struct* const base){
  return (bool)(*base -> IDR >> base -> PIN_NUM) & 1;
}
