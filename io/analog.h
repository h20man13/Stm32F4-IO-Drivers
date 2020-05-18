#ifndef ANALOG_H
#define ANALOG_H

#include <stdint.h>
#include "io.h"
#include "../data_structures/linkedList.h"

template <typename T> class ANALOG{
  public:
  ANALOG();
  ~ANALOG();
  T read();
  private:
  void update_seq_regs(ANALOG*);
  static linkedList<ANALOG> list;
  uint32_t seq_number;
  static T counts[16];
};

#endif
