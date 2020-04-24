#ifndef TIMER_PRE
#define TIMER_PRE

#include <stdint.h>

typedef uint32_t pre_val;

inline pre_val Sample_Prescalar(pre_val (*func)());
inline void Configure_Prescalar(void (*func)());

pre_val PLLN();
pre_val PLLP();
pre_val PLLM();

pre_val AHB1();
pre_val APB1();
pre_val APB2();

#endif