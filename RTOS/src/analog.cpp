#include "analog.h"

const static uint32_t* ADC_SQR1 = (uint32_t*)0x4001202C; //base seq addr
const static uint32_t* ADC_SQR3 = (uint32_t*)0x40012034;
const static uint32_t* ADC_SMP1 = (uint32_t*)0x4001200C;
const static uint32_t* ADC_CR1 = (uint32_t*)0x40012004;
const static uint32_t* ADC_CR2 = (uint32_t*)0x40012008;
const static uint32_t* DMA_PAR = (uint32_t*)0x40026018;
const static uint32_t* DMA_MA = (uint32_t*)0x4002601C;
const static uint32_t* DMA_CR = (uint32_t*)0x40026010;
const static uint32_t* ADC_DATA = (uint32_t*)0x4001204C;
const static uint32_t* DMA_NDTR = (uint32_t*)0x40026014;

template <class T> ANALOG<T>::ANALOG(GPIO_Pin p){
    clear(ADC_CR2, 1, 0);
    seq_number = in(ADC_SQR1, 4, 20);
    out(ADC_SQR1, 4, 20, seq_number + 1);
    Analog_Gpio(gpioa, p);
    Analog_Gpio.Configure_MODER(input);
    Analog_Gpio.Configure_OTYPER(push_pull);
    list.add(this); //add to list to suntract sequence #s from the other objects so read operation still works
    uint32_t reg_val = p / 10;
    uint32_t over = p % 10;
    out(ADC_SMP1 + reg_val, 3, over * 3, 7); //set sampling spped to max
    reg_val = seq_number / 6; //to get seq_Addr
    over = seq_number % 6; //to get location in seq_addr
    out(ADC_SQR3 - reg_val, 5, over * 5, (uint32_t)p);
    out(DMA_NDTR, 16, 0, seq_number);
    if(seq_number == 0){
        out(ADC_CR1, 1, 8, 1); //scan bit set
        out(ADC_CR2, 1, 8, 1); //dma bit set
        out(DMA_PAR, 32, 0, ADC_DATA);
        out(DMA_MA, 32, 0, counts);
        out(DMA_CR, 1, 8, 1); //dma circ bit set
        out(DMA_CR, 1, 10, 1); //memory incriment mode
        out(DMA_CR, 2, 13, 2); //memsize
        out(DMA_CR, 2, 11, 2); //persize
        out(DMA_CR, 1, 0, 1); //dma enable
        out(ADC_CR2, 1, 1, 1); //continious mode
    }
    out(ADC_CR2, 1, 0, 1); //enable adc
}

template <class T> void ANALOG<T>::update_seq_regs(ANALOG* list_object){
    if(seq_number < list_object -> seq_number){
        uint32_t addr = seq_number / 6;
        uint32_t sub_addr = seq_number % 6;
        uint32_t storage = in(ADC_SQR3 - addr, 5, (sub_addr + 1) * 5);
        out(ADC_SQR3 - addr, 5, sub_addr * 5, storage);
        list_object -> seq_number--;
    }
}

template <class T> ANALOG<T>::~ANALOG(){
    list.list_func(this -> update_seq_regs);
    list.remove(this);
    uint32_t cur = in(ADC_SQR1, 4, 20);
    cur--;
    out(ADC_SQR1, 4, 20, cur);
    if(seq_number == 0){ //none left
        clear(DMA_CR, 1, 0); //disable dma
        clear(ADC_CR2, 1, 0);
        clear(ADC_CR1, 1, 8); //scan bit set
        clear(ADC_CR2, 1, 8); //dma bit set
        clear(DMA_PAR, 32, 0);
        clear(DMA_MA, 32, 0);
        clear(DMA_CR, 1, 8); //dma circ bit set
        clear(DMA_CR, 1, 10); //memory incriment mode
        clear(DMA_CR, 2, 13); //memsize
        clear(DMA_CR, 2, 11); //persize
        clear(ADC_CR2, 1, 1); //continious mode
    }
}

template <class T> T ANALOG<T>::read(){
    return counts[seq_number];
}
