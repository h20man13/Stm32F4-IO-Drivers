#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stdbool.h>

#include "../timer/rcc.h"
#include "../shared.h"

typedef enum{
  p0,
  p1,
  p2,
  p3,
  p4,
  p5,
  p6,
  p7,
  p8,
  p9,
  p10,
  p11,
  p12,
  p13
} GPIO_Pin;

//init the gpio struct
typedef struct{
  GPIO_Pin PIN_NUM;
  uint32_t* MODER;
  uint32_t* OSPEEDR;
  uint32_t* PUPDR;
  volatile uint32_t* IDR;
  uint32_t* OTYPER;
  uint32_t* ODR;
}GPIO_Struct;

//GPIO init adress
typedef enum{
  gpioa = 0x40020000,
  gpiob = 0x40020400,
  gpioc = 0x40020800,
  gpiod = 0x40020C00,
  gpioe = 0x40021000
} GPIO;
//Moder register values
typedef enum{
  input = 0b00,
  output = 0b01,
  alternate = 0b10,
  analog = 0b11
} MODER;

typedef enum{
  low_speed = 0b00,
  mid_speed = 0b01,
  high_speed = 0b10,
  very_high_speed = 0b11
} OSPEEDR;

typedef enum{
  none = 0b00,
  pull_up = 0b01,
  pull_down = 0b10
} PUPDR;

typedef enum{
  push_pull = 0,
  open_drain = 1
} OTYPER;

//Basic GPIO Methods
void Init_GPIO(GPIO_Struct* const, const GPIO, const GPIO_Pin);
void Disable_GPIO(GPIO_Struct* const);
void Configure_MODER(GPIO_Struct* const, const MODER);
void Configure_OSPEEDR(GPIO_Struct* const, const OSPEEDR);
void Configure_PUPDR(GPIO_Struct* const, const PUPDR);
void Configure_OTYPER(GPIO_Struct* const, const OTYPER);
void Configure_ODR(GPIO_Struct* const, const STATE);
bool Sample_IDR(GPIO_Struct* const);
#endif
