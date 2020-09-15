#ifndef SHARED_H
#define SHARED_H

typedef enum{
  off = 0,
  on = 1
}STATE;
typedef enum{
  unlocked = 0,
  locked = 1
}LOCK;

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

//GPIO init adress
typedef enum{
  gpioa = 0x40020000,
  gpiob = 0x40020400,
  gpioc = 0x40020800,
  gpiod = 0x40020C00,
  gpioe = 0x40021000
} GPIO_Addr;

//Moder register values
typedef enum{
  input = 0b00,
  output = 0b01,
  alternate = 0b10,
  analog = 0b11
} MODER_vals;

typedef enum{
  low_speed = 0b00,
  mid_speed = 0b01,
  high_speed = 0b10,
  very_high_speed = 0b11
} OSPEEDR_vals;

typedef enum{
  none = 0b00,
  pull_up = 0b01,
  pull_down = 0b10
} PUPDR_vals;

typedef enum{
  push_pull = 0,
  open_drain = 1
} OTYPER_vals;

#endif
