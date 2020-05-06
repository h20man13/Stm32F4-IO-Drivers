#include "timer_src.h"

static src_val SYS_CLK_MUX;
static src_val PLL_SRC_MUX;
//initial clock getter functions
src_val Get_SYS_SRC(){
    return SYS_CLK_MUX;
}

src_val Get_PLL_MUX(){
    return PLL_SRC_MUX;
}

void Change_SYS_SRC(src_val TO){
  SYS_CLK_MUX = TO;
}

void Change_PLL_MUX(src_val TO){
  PLL_SRC_MUX = TO;
}