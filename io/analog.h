#ifndef ANALOG_H
#define ANALOG_H

#include <stdint>
#include "gpio.h"

typedef struct{
  GPIO_Struct gpio;
} ANALOG_Struct;

void Init_ANALOG(ANALOG_Struct*,Pin,);
#endif
