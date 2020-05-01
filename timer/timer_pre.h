#ifndef TIMER_PRE
#define TIMER_PRE

#include <stdint.h>
#include "../io/io.h"

typedef uint32_t pre_val;
typedef void pre_void;

inline pre_val Sample_Prescalar(pre_val(*)());
inline void Configure_Prescalar(pre_void(*)());

pre_val PLLN();
pre_val PLLP();
pre_val PLLM();
pre_val AHB1();
pre_val APB1();
pre_val APB2();

pre_void AHB1(pre_val);
pre_void APB1(pre_val);
pre_void PLLN(pre_val);
pre_void PLLP(pre_val);
pre_void PLLM(pre_val);
pre_void APB2(pre_val);

#endif