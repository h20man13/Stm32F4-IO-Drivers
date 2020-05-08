#include <stdbool.h>

#include "io/gpio.h"
#include "math/rand.h"

void sleep(uint32_t f)
{
  for(volatile uint32_t i = 0; i < f; i++);
}

int main()
{
  //Initialize seed
  seed(64);
  //initialize structs to hold adresses
  GPIO startbutton(gpioc, p13);
  startbutton.Configure_MODER(input);
  startbutton.Configure_PUPDR(none);

  GPIO led1(gpioc, p12);
  led1.Configure_MODER(output);
  led1.Configure_OTYPER(push_pull);

  GPIO led2(gpioc, p0);
  led2.Configure_MODER(output);
  led2.Configure_OTYPER(push_pull);

  GPIO led3(gpioc, p9);
  led3.Configure_MODER(output);
  led3.Configure_OTYPER(push_pull);

  GPIO led4(gpioa, p10);
  led4.Configure_MODER(output);
  led4.Configure_OTYPER(push_pull);

  GPIO button1(gpioc, p10);
  button1.Configure_MODER(input);
  button1.Configure_PUPDR(none);

  GPIO button2(gpioc, p3);
  button2.Configure_MODER(input);
  button2.Configure_PUPDR(none);

  GPIO button3(gpioc, p8);
  button3.Configure_MODER(input);
  button3.Configure_PUPDR(none);

  GPIO button4(gpioc, p4);
  button4.Configure_MODER(input);
  button4.Configure_PUPDR(none);

  //wait for user to start game loop
  while(true){
    if(startbutton.Sample_IDR()){
      while(startbutton.Sample_IDR());
      break;
    }
  }
  uint32_t size = 1;
  uint32_t time_Allowed = 1000000;
  GPIO* outputs[4];
  outputs[0] = &led1;
  outputs[1] = &led2;
  outputs[2] = &led3;
  outputs[3] = &led4;

  GPIO* inputs[4];
  inputs[0] = &button1;
  inputs[1] = &button2;
  inputs[2] = &button3;
  inputs[3] = &button4;
  //main game loop
  while(true)
  {
    int turn[size];
    for(int i = 0; i < size; i++){
      turn[i] = sudo_randomUint32() % size;
    }
    for(int i = 0; i < size; i++){
      outputs[turn[i]] -> Configure_ODR(on);
      sleep(100000);
      outputs[turn[i]] -> Configure_ODR(off);
      sleep(100000);
    }
    for(int i = 0; i < size; i++){
      int z = time_Allowed;
      while(z > 0){
	      for(int x = 0; x < 4; x++){
	        if(x == turn[i] && inputs[x] -> Sample_IDR()){
	          outputs[x] -> Configure_ODR(on);
	          while(inputs[x] -> Sample_IDR());
	          outputs[x] -> Configure_ODR(off);
	          goto next_turn;
	        }
	        else if(x != turn[i] && inputs[x] -> Sample_IDR()){
	          outputs[x] -> Configure_ODR(on);
            while(inputs[x] -> Sample_IDR());
            outputs[x] -> Configure_ODR(off);
            outputs[x] -> Configure_ODR(on);
            sleep(10000);
            outputs[turn[i]] -> Configure_ODR(off);
            sleep(10000);
            outputs[turn[i]] -> Configure_ODR(on);
            sleep(10000);
            outputs[turn[i]] -> Configure_ODR(off);
            sleep(10000);
            outputs[turn[i]] -> Configure_ODR(on);
            sleep(10000);
            outputs[turn[i]] -> Configure_ODR(off);
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
 end_game: led1.Configure_ODR(on);
 led2.Configure_ODR(on);
 led3.Configure_ODR(on);
 led4.Configure_ODR(on);
 sleep(10000);
 led1.Configure_ODR(off);
 led2.Configure_ODR(off);
 led3.Configure_ODR(off);
 led4.Configure_ODR(off);
 sleep(10000);
 led1.Configure_ODR(on);
 led2.Configure_ODR(on);
 led3.Configure_ODR(on);
 led4.Configure_ODR(on);
 sleep(10000);
 led1.Configure_ODR(off);
 led2.Configure_ODR(off);
 led3.Configure_ODR(off);
 led4.Configure_ODR(off);
 sleep(10000);
 led1.Configure_ODR(on);
 led2.Configure_ODR(on);
 led3.Configure_ODR(on);
 led4.Configure_ODR(on);
 sleep(10000);
 led1.Configure_ODR(off);
 led2.Configure_ODR(off);
 led3.Configure_ODR(off);
 led4.Configure_ODR(off);
 sleep(10000);
 led1.Configure_ODR(on);
 led2.Configure_ODR(on);
 led3.Configure_ODR(on);
 led4.Configure_ODR(on);
 sleep(10000);
 led1.Configure_ODR(off);
 led2.Configure_ODR(off);
 led3.Configure_ODR(off);
 led4.Configure_ODR(off);
 sleep(10000);
}
