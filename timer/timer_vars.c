const static uint32_t HSI = 16000000;
const static uint32_t HSE = 8000000;
const static uint32_t LSI = 32000;

uint32_t (*PLL_SRC_MUX)() = NULL;
uint32_t (*System_CLK_MUX)() = NULL;

typedef uint32_t prescaler_val;
typedef uint32_t speed_val;

//initial clock getter functions

speed_val HSI(){
  return HSI;
}

speed_val HSE(){
  return HSE;
}

speed_val LSI(){
  return LSI;
}

//Headers for sample functions

uint32_t Sample_Clock_Speed(speed_val (*Clock)());
uint32_t Configure_Clock_Speed(void (*Clock)(uint32_t), uint32_t speed);
void Change_MUX(uint32_t (*MUX)(), uint32_t(*SRC)());
uint32_t Sample_Prescaler(prescalar_val (*prescaler)());
//Accesor Methods for prescalers

const static uint32_t pll_point = 0x40023804;

prescaler_val PLLN(){
  return (prescalar_val)((*(pll_point) >> 6) & 0b111111111);
}

prescalar_val PLLP(){
  return (prescalar_val)(1 << (((*(pll_point) >> 16) & 0b11) + 1));
}

prescalar_val PLLM(){
  return (prescalar_val)(*(pll_point) & 0b111111);
}

prescalar_val AHB1(){
  int32_t HPRE = (((*(sys_point) >> 4) & 0b1111) - 0b1000) + 1;
  if(HPRE < 0){
    HPRE = 0;
  }
  else if(HPRE >= 4){
    HPRE++;
  }
  return (prescalar_val)(1 << HPRE);
}

prescalar_val APB1(){
  int32_t PPRE1 = ((((*(sys_point) >> 9) & 0b111) - 0b100) + 1);
  if(PPRE1 < 0){
    PPRE1 = 0;
  }
  return (prescalar_val)(1 << PPRE1);
}

prescalar_val APB2(){
  int32_t PPRE2 = (((*(sys_point) >> 12) & 0b111) - 0b100) + 1;
  if(PPRE2 < 0){
    PPRE2 = 0;
  }
  return (prescalar_val)(1 << PPRE2);
}

//Accesor Methods for Clock Speeds

uint32_t PLL(){
  uint32_t* pll_point = (uint32_t*)0x40023804;
  uint32_t src = Sample_CLock_Speed(PLL_SRC_MUX);
  uint32_t M = Sample_Prescalar(PLLM);
  uint32_t N = Sample_Prescalar(PLLN);
  uint32_t P = Sample_Prescalar(PLLP);
  return src / M * N / P
}

uint32_t SYSCLK(){
  return Sample_Clock_Speed(System_CLK_MUX);
}

uint32_t AHB1(){
  uint32_t* sys_point = (uint32_t*)0x40033808;
  uint32_t src = Sample_Clock_Speed(SYSCLK);
  uint32_t HPRE = Sample_Prescaler(AHB1);
  return src / HPRE
}

uint32_t APB2(){
  uint32_t* cfg_point = (uint32_t*)0x40033808;
  uint32_t src = Sample_Clock_Speed(AHB1);
  uint32_t PPRE2 = (((*(sys_point) >> 12) & 0b111) - 0b100) + 1;
  if(PPRE2 <= 0){
    `return src;
  }
  PPRE2 = 1 << PPRE2;
  return src / PPRE2;
}

uint32_t APB1(){
   uint32_t* cfg_point = (uint32_t*)0x40033808;
   uint32_t src = Sample_Clock_Speed(AHB1);
   uint32_t PPRE1 = (((*(sys_point) >> 9) & 0b111) - 0b100) + 1;
   if(PPRE1 <= 0){
     return src;
   }
   PPRE1 = 1 << PPRE1;
   return src / PPRE1;
}

uint32_t ADC1(){
  uint32_t* cfg_point = (uint32_t*)0x40012304;
  uint32_t src = Sample_Clock_Speed(APB2);
  uint32 ADCPRE = 1 << ((((*(cfg_point) >> 16) & 0b11) + 1);
  return src / ADCPRE; 
}

//Mutator Methods
void ADC1(uint32_t speed){
    uint32_t* cfg_point = (uint32_t*)0x40012304;
    uint32_t hl = Sample_Clock_Speed(ADC1);
    if(h1 > speed)
    {
      int change = h1 - speed;
      do{
	int save_change = change;
        int value = (((((*(cfg_point) >> 16) & 0b11) - 1);
	if(value < 0){
	  break;
	}
	*cfg_point &= (~(0b11 << 16));
	*cfg_point |= value << 16;
	h1 = Sample_Clock_Speed(ADC1);
        change = (h1 > speed) ? h1 - speed : speed - h1;
	if(change >= save_change){
	  int value = (((((*(cfg_point) >> 16) & 0b11) + 1);
	  *cfg_point &= (~(0b11 << 16));
	  *cfg_point |= value << 16;
	  break;
	}
      }while(1);
    }
    else if(h1 < speed){
       int change = speed - h1;
      do{
	int save_change = change;
        int value = (((((*(cfg_point) >> 16) & 0b11) + 1);
	if(value > 3){
	  break;
	}
	*cfg_point &= (~(0b11 << 16));
	*cfg_point |= value << 16;
	h1 = Sample_Clock_Speed(ADC1);
	change = (speed > h1) ? speed - h1 : h1 - speed;
	if(change >= save_change){
	  int value = (((((*(cfg_point) >> 16) & 0b11) - 1);
	  *cfg_point &= (~(0b11 << 16));
	  *cfg_point |= value << 16;
	  break;
	}
      }while(1);
    }
}
void APB1(uint32_t speed){
    uint32_t* cfg_point = (uint32_t*)0x40033808;
    uint32_t hl = Sample_Clock_Speed(APB1);
    if(h1 > speed)
    {
      int change = h1 - speed;
      do{
	int save_change = change;
        int value = (((((*(cfg_point) >> 16) & 0b11) - 1);
	if(value < 0){
	  break;
	}
	*cfg_point &= (~(0b11 << 16));
	*cfg_point |= value << 16;
	h1 = Sample_Clock_Speed(ADC1);
        change = (h1 > speed) ? h1 - speed : speed - h1;
	if(change >= save_change){
	  int value = (((((*(cfg_point) >> 16) & 0b11) + 1);
	  *cfg_point &= (~(0b11 << 16));
	  *cfg_point |= value << 16;
	  break;
	}
      }while(1);
    }
    else if(h1 < speed){
       int change = speed - h1;
      do{
	int save_change = change;
        int value = (((((*(cfg_point) >> 16) & 0b11) + 1);
	if(value > 3){
	  break;
	}
	*cfg_point &= (~(0b11 << 16));
	*cfg_point |= value << 16;
	h1 = Sample_Clock_Speed(ADC1);
	change = (speed > h1) ? speed - h1 : h1 - speed;
	if(change >= save_change){
	  int value = (((((*(cfg_point) >> 16) & 0b11) - 1);
	  *cfg_point &= (~(0b11 << 16));
	  *cfg_point |= value << 16;
	  break;
	}
      }while(1);
    }
}


//Holder Methods

void Change_MUX(uint32_t (*MUX)(), uint32_t (*SRC)()){
  MUX = src;
}

uint32_t Sample_Prescaler(prescalar_val (*prescaler)()){
  return (uint32_t)(*prescaler)();
}
uint32_t Sample_Clock_Speed(uint32_t (*Clock)()){
  return (*Clock)();
}

void Configure_Clock_Speed(void(*Clock)(uint32_t), uint32_t speed){
  (*Clock)(speed);
}
