#ifndef SHARED_H
#define SHARED_H

#define PLLN(...) _Generic((PLLN(...)), pre_val: pre_PLLN_get(...), pre_void: pre_PLLN_set(...));
#define PLLP(...) _Generic((PLLP(...)), pre_val: pre_PLLP_get(...), pre_void: pre_PLLP_set(...));
#define PLLM(...) _Generic((PLLM(...)), pre_val: pre_PLLM_get(...), pre_void: pre_PLLM_set(...));
#define AHB1(...) _Generic((AHB1(...)), pre_val: pre_AHB1_get(...), pre_void: pre_AHB1_set(...));
#define APB1(...) _Generic((APB1(...)), pre_val: pre_APB1_get(...), pre_void: pre_APB1_set(...));
#define APB2(...) _Generic((APB2(...)), pre_val: pre_APB2_get(...), pre_void: pre_APB2_set(...));

typedef enum{
  off = 0,
  on = 1
}STATE;
typedef enum{
  unlocked = 0,
  locked = 1
}LOCK;

#endif
