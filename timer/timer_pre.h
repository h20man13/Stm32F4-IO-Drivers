#ifndef TIMER_PRE
#define TIMER_PRE

#include <stdint.h>

typedef uint32_t pre_val;

inline pre_val PLLN();
inline pre_val PLLP();
inline pre_val PLLM();

pre_val AHB1();
pre_val APB1();
pre_val APB2();

#endif