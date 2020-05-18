#include "analog.h"

const uint32_t* ADC_SQR1 = (uint32_t*)0x4001202C;

template <class T> ANALOG<T>::ANALOG(){
    seq_number = in(ADC_SQR1, 4, 20) + 1;
    out(ADC_SQR1, 4, 20, seq_number);
    list.add(this);
}

template <class T> void ANALOG<T>::update_seq_regs(ANALOG* list_object){
    if(seq_number < list_object -> seq_number){
        list_object -> seq_number--;
    }
}

template <class T> ANALOG<T>::~ANALOG(){
    list.list_func(this -> update_seq_regs);
    list.remove(this);
    uint32_t cur = in(ADC_SQR1, 4, 20);
    cur--;
    out(ADC_SQR1, 4, 20, cur);
}

template <class T> T ANALOG<T>::read(){
    return counts[seq_number];
}
