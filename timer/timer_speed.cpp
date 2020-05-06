#include "timer_speed.h"
#include "timer_pre.h"
#include "timer_src.h"

static clk_speed PLL_SRC_MUX(){
    return (clk_speed)Get_PLL_MUX();
}
static clk_speed SYS_CLK_MUX(){
    return (clk_speed)Get_SYS_SRC();
}
clk_speed PLL(){
  clk_speed src = Sample_Clock_Speed(PLL_SRC_MUX);
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
  pre_val HPRE = Sample_Prescalar(AHB1);
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

void PLL(clk_speed target){
  clk_speed cur = Sample_Clock_Speed(PLL);
}

clk_void ADC1(clk_speed target){
  clk_speed past = Sample_Clock_Speed(ADC1);
  if(target > past){
    pre_val cur_pre;
    do{
      cur_pre = Sample_Prescalar(ADC1);
      cur_pre -= 2;
      Configure_Prescalar(ADC1, cur_pre);
      past = Sample_Clock_Speed(ADC1);
    }while(target > past);
    if(past != target){
      cur_pre += 2;
      Configure_Prescalar(ADC1, cur_pre);
    }
  }
  else if(target < past){
    do{
      pre_val cur_pre = Sample_Prescalar(ADC1);
      cur_pre += 2;
      Configure_Prescalar(ADC1, cur_pre);
      past = Sample_Clock_Speed(ADC1);
    }while(target < past);
  }
}
