#ifndef ANALOG_H
#define ANALOG_H

#include <stdint.h>
#include "io.h"
#include "gpio.h"
#include "../shared.h"
#include "../data_structures/linkedList.h"

template <typename T> class ANALOG{
  public:
  ANALOG(GPIO_Pin);
  ~ANALOG();
  T read();
  private:
  void update_seq_regs(ANALOG*);
  uint32_t seq_number;
  GPIO Analog_Gpio;
  static linkedList<ANALOG*> list;
  static uint32_t counts[16];
};

#endif
