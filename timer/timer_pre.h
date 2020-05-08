#ifndef TIMER_PRE
#define TIMER_PRE

#include <stdint.h>
#include "../io/io.h"
#include "../math/algebra.h"

class pre{
    public:
    uint32_t PLLN(void);
    uint32_t PLLP(void);
    uint32_t PLLM(void);
    uint32_t AHB1(void);
    uint32_t APB1(void);
    uint32_t APB2(void);
    uint32_t ADC1(void);

    void AHB1(uint32_t);
    void APB1(uint32_t);
    void PLLN(uint32_t);
    void PLLP(uint32_t);
    void PLLM(uint32_t);
    void APB2(uint32_t);
    void ADC1(uint32_t);
};

uint32_t Sample_Prescalar(uint32_t (pre::*)());
void Configure_Prescalar(void (pre::*)(uint32_t), uint32_t);

#endif