#include "timer_enable.h"
#include <stdint.h>

static uint32_t* const AHB1_ENR = (uint32_t* const)0x40023800;

void enable_timer(GPIO_Addr v){
    out(AHB1_ENR, 1, (v - gpioa)/0x400, v);
}

void disable_timer(GPIO_Addr v){
    clear(AHB1_ENR, 1, (v - gpioa)/0x400);
}