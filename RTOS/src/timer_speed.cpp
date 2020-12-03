#include "timer_speed.h"

const static clk clk_sv;

uint32_t Sample_Clock_Speed(uint32_t (clk::*src)() const){
  return (clk_sv.*src)();
}

void Configure_Clock_Speed(void (clk::*f)(uint32_t) const, uint32_t var){
  (clk_sv.*f)(var);
}

uint32_t clk::PLL_SRC_MUX(){
    return Get_PLL_MUX();
}
uint32_t clk::SYS_CLK_MUX(){
    return Get_SYS_SRC();
}

uint32_t clk::PLL(){
  uint32_t src = Sample_Clock_Speed(&clk::PLL_SRC_MUX);
  uint32_t M = Sample_Prescalar(&pre::PLLM);
  uint32_t N = Sample_Prescalar(&pre::PLLN);
  uint32_t P = Sample_Prescalar(&pre::PLLP);
  return src / M * N / P;
}

uint32_t clk::SYS_CLK(){
  return Sample_Clock_Speed(&clk::SYS_CLK_MUX);
}

uint32_t clk::AHB1(){
  uint32_t src = Sample_Clock_Speed(&clk::SYS_CLK);
  uint32_t HPRE = Sample_Prescalar(&pre::AHB1);
  return src / HPRE;
}

uint32_t clk::APB2(){
  uint32_t src = Sample_Clock_Speed(&clk::AHB1);
  uint32_t PPRE2 = Sample_Prescalar(&pre::APB2);
  return src / PPRE2;
}

uint32_t clk::APB1(){
   uint32_t src = Sample_Clock_Speed(&clk::AHB1);
   uint32_t PPRE1 = Sample_Prescalar(&pre::APB1);
   return src / PPRE1;
}

uint32_t clk::ADC1(){
  uint32_t src = Sample_Clock_Speed(&clk::APB2);
  uint32_t ADCPRE = Sample_Prescalar(&pre::ADC1);
  return src / ADCPRE; 
}

void clk::AHB1(uint32_t target){
  if(target >= 0 && target < 0x501BD00){
    uint32_t past = Sample_Clock_Speed(&clk::AHB1);
    uint32_t APB1_save = Sample_Clock_Speed(&clk::APB1);
    uint32_t APB2_save = Sample_Clock_Speed(&clk::APB2);
    if(target > past){
      uint32_t cur_pre;
      do{
        cur_pre = Sample_Prescalar(&pre::AHB1);
        cur_pre /= 2;
        if(cur_pre == 32){
          cur_pre /= 2;
        }
        Configure_Prescalar(&pre::AHB1, cur_pre);
        past = Sample_Clock_Speed(&clk::AHB1);
      }while(target > past);
      if(past != target){
        cur_pre *= 2;
        Configure_Prescalar(&pre::AHB1, cur_pre);
      }
      Configure_Clock_Speed(&clk::APB1, APB1_save);
      Configure_Clock_Speed(&clk::APB2, APB2_save);
    }
    else if(target < past){
      do{
        uint32_t cur_pre = Sample_Prescalar(&pre::AHB1);
        cur_pre *= 2;
        if(cur_pre == 32){
          cur_pre *= 2;
        }
        Configure_Prescalar(&pre::AHB1, cur_pre);
        past = Sample_Clock_Speed(&clk::AHB1);
      }while(target < past);
      Configure_Clock_Speed(&clk::APB1, APB1_save);
      Configure_Clock_Speed(&clk::APB2, APB2_save);
    }
  }
}

void clk::APB2(uint32_t target){
  if(target >= 0 && target < 0x501BD00){
    uint32_t past = Sample_Clock_Speed(&clk::APB2);
    uint32_t ADC1_save = Sample_Clock_Speed(&clk::ADC1);
    if(target > past){
      uint32_t cur_pre;
      do{
        cur_pre = Sample_Prescalar(&pre::APB2);
        cur_pre /= 2;
        Configure_Prescalar(&pre::APB2, cur_pre);
        past = Sample_Prescalar(&pre::APB2);
      }while(target > past);
      if(past != target){
        cur_pre *= 2;
        Configure_Prescalar(&pre::APB2, cur_pre);
      }
      Configure_Clock_Speed(&clk::ADC1, ADC1_save);
    }
    else if(target < past){
      do{
        uint32_t cur_pre = Sample_Prescalar(&pre::APB2);
        cur_pre *= 2;
        Configure_Prescalar(&pre::APB2, cur_pre);
      }while(target < past);
      Configure_Clock_Speed(&clk::ADC1, ADC1_save);
    }
  }
}

void clk::APB1(uint32_t target){
  if(target >= 0 && target < 0x280DE80){
    uint32_t past = Sample_Clock_Speed(&clk::APB1);
    if(target > past){
      uint32_t cur_pre;
      do{
        cur_pre = Sample_Prescalar(&pre::APB1);
        cur_pre /= 2;
        Configure_Prescalar(&pre::APB1, cur_pre);
        past = Sample_Prescalar(&pre::APB1);
      }while(target > past);
      if(past != target){
        cur_pre *= 2;
        Configure_Prescalar(&pre::APB1, cur_pre);
      }
    }
    else if(target < past){
      do{
        uint32_t cur_pre = Sample_Prescalar(&pre::APB1);
        cur_pre *= 2;
        Configure_Prescalar(&pre::APB1, cur_pre);
      }while(target < past);
    }
  }
}

void clk::ADC1(uint32_t target){
  uint32_t past = Sample_Clock_Speed(&clk::ADC1);
  if(target > past){
    uint32_t cur_pre;
    do{
      cur_pre = Sample_Prescalar(&pre::ADC1);
      cur_pre -= 2;
      Configure_Prescalar(&pre::ADC1, cur_pre);
      past = Sample_Clock_Speed(&clk::ADC1);
    }while(target > past);
    if(past != target){
      cur_pre += 2;
      Configure_Prescalar(&pre::ADC1, cur_pre);
    }
  }
  else if(target < past){
    do{
      uint32_t cur_pre = Sample_Prescalar(&pre::ADC1);
      cur_pre += 2;
      Configure_Prescalar(&pre::ADC1, cur_pre);
      past = Sample_Clock_Speed(&clk::ADC1);
    }while(target < past);
  }
}