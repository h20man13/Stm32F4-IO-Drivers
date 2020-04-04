#include <stdbool.h>
#include "io/gpio.h"

void sleep(uint32_t f)
{
  for(volatile uint32_t i = 0; i < f; i++);
}
int main()
{
  //initialize structs to hold adresses
  GPIO_Struct startbutton;
  GPIO_Struct led1;
  GPIO_Struct led2;
  GPIO_Struct led3;
  GPIO_Struct led4;
  GPIO_Struct button1;
  GPIO_Struct button2;
  GPIO_Struct button3;
  GPIO_Struct button4;
  //configure the pins to the necissary states
  Init_GPIO(&startbutton, gpioc, p13);
  Configure_MODER(&startbutton, input);
  Configure_PUPDR(&startbutton, none);

  Init_GPIO(&button1, gpioc, p10);
  Configure_MODER(&button1, input);
  Configure_PUPDR(&startbutton, none);

  Init_GPIO(&button2, gpioc, p3);
  Configure_MODER(&button2, input);
  Configure_PUPDR(&button2, none);

  Init_GPIO(&button3, gpioc, p8);
  Configure_MODER(&button3, input);
  Configure_PUPDR(&button3, none);

  Init_GPIO(&button4, gpioc, p4);
  Configure_MODER(&button4, input);
  Configure_PUPDR(&button4, none);

  Init_GPIO(&led1, gpioc, p12);
  Configure_MODER(&led1, output);
  Configure_OTYPER(&led1, push_pull);

  Init_GPIO(&led2, gpioc, p0);
  Configure_MODER(&led2, output);
  Configure_OTYPER(&led2, push_pull);

  Init_GPIO(&led3, gpioc, p9);
  Configure_MODER(&led3, output);
  Configure_OTYPER(&led3, push_pull);

  Init_GPIO(&led4, gpioa, p10);
  Configure_MODER(&led4, output);
  Configure_OTYPER(&led4, push_pull);

  //wait for user to start game loop
  while(true){
    if(Sample_IDR(&startbutton)){
      while(Sample_IDR(&startbutton));
      break;
    }
  }
  uint32_t size = 1;
  uint32_t time_Allowed = 1000000;
  GPIO_Struct* outputs[4];
  outputs[0] = &led1;
  outputs[1] = &led2;
  outputs[2] = &led3;
  outputs[3] = &led4;

  GPIO_Struct* inputs[4];
  inputs[0] = &button1;
  inputs[1] = &button2;
  inputs[2] = &button3;
  inputs[3] = &button4;
  //main game loop
  while(true)
  {
    int turn[size];
    for(int i = 0; i < size; i++){
      //turn[i] = rand() % size; use own random function
     }
    for(int i = 0; i < size; i++){
      Configure_ODR(outputs[turn[i]], on);
      sleep(100000);
      Configure_ODR(outputs[turn[i]], off);
      sleep(100000);
    }
    for(int i = 0; i < size; i++)
    {
      int z = time_Allowed;
      while(z > 0)
      {
	for(int x = 0; x < 4; x++)
	{
	  if(x == turn[i] && Sample_IDR(inputs[x]))
	  {
	    Configure_ODR(outputs[x], on);
	    while(Sample_IDR(inputs[x]));
	    Configure_ODR(outputs[x], off);
	    goto next_turn;
	  }
	  else if(x != turn[i] && Sample_IDR(inputs[x]))
	  {
	    Configure_ODR(outputs[x], on);
            while(Sample_IDR(inputs[x]));
	    Configure_ODR(outputs[x], off);
	    Configure_ODR(outputs[turn[i]], on);
	    sleep(10000);
	    Configure_ODR(outputs[turn[i]], off);
	    sleep(10000);
	    Configure_ODR(outputs[turn[i]], on);
            sleep(10000);
            Configure_ODR(outputs[turn[i]], off);
            sleep(10000);
	    Configure_ODR(outputs[turn[i]], on);
            sleep(10000);
            Configure_ODR(outputs[turn[i]], off);
            sleep(10000);
	    goto end_game;
	  }
	}
	z -= 2;
      }
      goto end_game;
    next_turn: sleep(0);
    }
    time_Allowed -= 2;
  }
 end_game:
 Configure_ODR(&led1, on);
 Configure_ODR(&led2, on);
 Configure_ODR(&led3, on);
 Configure_ODR(&led4, on);
 sleep(10000);
 Configure_ODR(&led1, off);
 Configure_ODR(&led2, off);
 Configure_ODR(&led3, off);
 Configure_ODR(&led4, off);
 sleep(10000);
 Configure_ODR(&led1, on);
 Configure_ODR(&led2, on);
 Configure_ODR(&led3, on);
 Configure_ODR(&led4, on);
 sleep(10000);
 Configure_ODR(&led1, off);
 Configure_ODR(&led2, off);
 Configure_ODR(&led3, off);
 Configure_ODR(&led4, off);
 sleep(10000);
 Configure_ODR(&led1, on);
 Configure_ODR(&led2, on);
 Configure_ODR(&led3, on);
 Configure_ODR(&led4, on);
 sleep(10000);
 Configure_ODR(&led1, off);
 Configure_ODR(&led2, off);
 Configure_ODR(&led3, off);
 Configure_ODR(&led4, off);
 sleep(10000);
 Configure_ODR(&led1, on);
 Configure_ODR(&led2, on);
 Configure_ODR(&led3, on);
 Configure_ODR(&led4, on);
 sleep(10000);
 Configure_ODR(&led1, off);
 Configure_ODR(&led2, off);
 Configure_ODR(&led3, off);
 Configure_ODR(&led4, off);
 sleep(10000);
}
