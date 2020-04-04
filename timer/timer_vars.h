#ifndef timer_vars
#define timer_vars
//holder functions
uint32_t Sample_Clock_Speed(void(*clock)());
uint32_t Configure_Clock_Speed(void(*Clock)(uint32_t), uint32_t);
uint32_t Change_MUX(uint32_t(**MUX)(), uint32_t(*SRC)());
//Accesors
uint32_t HSI();
uint32_t HSE();
uint32_t LSI();
uint32_t PLL();
uint32_t SYSCLK();
uint32_t AHB1();
uint32_t APB2();
uint32_t APB1();
uint32_t ADC1();
//Mutators
void ADC1();
#endif
