#ifndef TIMER_SPEED
#define TIMER_SPEED

#include <stdint.h>

typedef uint32_t clk_speed;
typedef void clk_void;

//helper methods

inline clk_speed Sample_Clock_Speed(clk_speed(*)());
inline clk_void Configure_Clock_Speed(clk_void(*)(clk_speed), clk_speed);

//Accesor Methods

clk_speed PLL();
clk_speed SYS_CLK();
clk_speed AHB1();
clk_speed APB2();
clk_speed APB1();
clk_speed ADC1();

clk_void PLL(clk_speed);
clk_void SYS_CLK(clk_speed);
clk_void AHB1(clk_speed);
clk_void APB2(clk_speed);
clk_void APB1(clk_speed);
clk_void ADC1(clk_speed);


#endif