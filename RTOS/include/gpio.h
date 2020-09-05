#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stdbool.h>

#include "shared.h"



class GPIO
{
  public:

  //Basic GPIO Methods
  GPIO(const GPIO_Addr, const GPIO_Pin);
  ~GPIO();
  void Configure_MODER(MODER_vals);
  void Configure_OSPEEDR(OSPEEDR_vals);
  void Configure_PUPDR(PUPDR_vals);
  void Configure_OTYPER(OTYPER_vals);
  void Configure_ODR(STATE);
  bool Sample_IDR();

  private:
  GPIO_Pin PIN_NUM;
  uint32_t* MODER;
  uint32_t* OSPEEDR;
  uint32_t* PUPDR;
  volatile uint32_t* IDR;
  uint32_t* OTYPER;
  uint32_t* ODR;

  static uint32_t counts[5];

};

#endif
