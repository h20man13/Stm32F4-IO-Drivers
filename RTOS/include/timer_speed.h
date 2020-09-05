#ifndef TIMER_SPEED
#define TIMER_SPEED

#include <stdint.h>

#include "timer_pre.h"
#include "timer_src.h"

//Accesor Methods
class clk{
    public:
    uint32_t PLL_SRC_MUX();
    uint32_t SYS_CLK_MUX();
    uint32_t PLL();
    uint32_t SYS_CLK();
    uint32_t AHB1();
    uint32_t APB2();
    uint32_t APB1();
    uint32_t ADC1();

    void PLL(uint32_t);
    void SYS_CLK(uint32_t);
    void AHB1(uint32_t);
    void APB2(uint32_t);
    void APB1(uint32_t);
    void ADC1(uint32_t);
};

uint32_t Sample_Clock_Speed(uint32_t(clk::*)());
void Configure_Clock_Speed(void(clk::*)(uint32_t), uint32_t);

#endif