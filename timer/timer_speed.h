#ifndef TIMER_SPEED
#define TIMER_SPEED

#include <stdint.h>

typedef uint32_t clk_speed;

//helper methods

inline clk_speed Sample_Clock_Speed(clk_speed (*func)());

//Accesor Methods

clk_speed PLL();
inline clk_speed SYS_CLK();
clk_speed AHB1();
clk_speed APB2();
clk_speed APB1();
clk_speed ADC1();

#endif