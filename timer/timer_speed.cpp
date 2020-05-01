#include "timer_speed.h"
#include "timer_pre.h"
#include "timer_src.h"

clk_speed PLL(){
  clk_speed src = Sample_CLock_Speed(PLL_SRC_MUX);
  pre_val M = Sample_Prescalar(PLLM);
  pre_val N = Sample_Prescalar(PLLN);
  pre_val P = Sample_Prescalar(PLLP);
  return src / M * N / P;
}

inline clk_speed SYSCLK(){
  return Sample_Clock_Speed(SYS_CLK_MUX);
}

clk_speed AHB1(){
  clk_speed src = Sample_Clock_Speed(SYSCLK);
  pre_val HPRE = Sample_Prescaler(AHB1);
  return src / HPRE;
}

clk_speed APB2(){
  clk_speed src = Sample_Clock_Speed(AHB1);
  pre_val PPRE2 = Sample_Prescalar(APB2);
  if(PPRE2 <= 0){
    return src;
  }
  return src / PPRE2;
}

clk_speed APB1(){
   clk_speed src = Sample_Clock_Speed(AHB1);
   pre_val PPRE1 = Sample_Prescalar(APB1);
   if(PPRE1 <= 0){
     return src;
   }
   PPRE1 = 1 << PPRE1;
   return src / PPRE1;
}

clk_speed ADC1(){
  clk_speed src = Sample_Clock_Speed(APB2);
  pre_val ADCPRE = Sample_Prescalar(ADC1);
  return src / ADCPRE; 
}
		     
inline clk_speed Sample_Clock_Speed(clk_speed (*src)()){
  return (*src)();
}