#ifndef TIMER_PRE
#define TIMER_PRE

#include <stdint.h>
#include "io.h"
#include "algebra.h"

class pre{
    public:
    uint32_t PLLN(void) const;
    uint32_t PLLP(void) const;
    uint32_t PLLM(void) const;
    uint32_t AHB1(void) const;
    uint32_t APB1(void) const;
    uint32_t APB2(void) const;
    uint32_t ADC1(void) const;

    void AHB1(uint32_t) const;
    void APB1(uint32_t) const;
    void PLLN(uint32_t) const;
    void PLLP(uint32_t) const;
    void PLLM(uint32_t) const;
    void APB2(uint32_t) const;
    void ADC1(uint32_t) const;
};

uint32_t Sample_Prescalar(uint32_t (pre::*)() const);
void Configure_Prescalar(void (pre::*)(uint32_t) const, uint32_t);

#endif
