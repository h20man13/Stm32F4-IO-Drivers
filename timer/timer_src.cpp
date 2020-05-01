#include "timer_src.h"

//initial clock getter functions


void Change_SYS_SRC(src_val TO){
  SYS_CLK_MUX = TO;
}

void Change_PLL_MUX(src_val TO){
  PLL_SRC_MUX = TO;
}