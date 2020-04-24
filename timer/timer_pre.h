#ifndef TIMER_PRE
#define TIMER_PRE

#include <stdint.h>

typedef uint32_t pre_val;
typedef void pre_void;

inline pre_val Sample_Prescalar(pre_val(*)());
inline void Configure_Prescalar(pre_void(*)());

pre_val pre_PLLN_get();
pre_val pre_PLLP_get();
pre_val pre_PLLM_get();
pre_val pre_AHB1_get();
pre_val pre_APB1_get();
pre_val pre_APB1_get();

pre_void pre_AHB1_set(pre_val);
pre_void pre_APB1_set(pre_val);
pre_void pre_PLLN_set(pre_val);
pre_void pre_PLLP_set(pre_val);
pre_void pre_PLLM_set(pre_val);
pre_void pre_APB2_set(pre_val);

#endif