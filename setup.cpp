#include <stdint.h>


extern "C" void reset_handler(){
    asm volatile("LDR r0, =_estack");
    asm volatile("MOV sp, r0");

    extern uint8_t* _sdata;
    extern uint8_t* _edata;
    extern uint8_t* _sidata;
    extern uint8_t* _sbss;
    extern uint8_t* _ebss;
    uint8_t* p = _sidata;

    extern void (*_spreinit_array []) (void) __attribute__((weak));
    extern void (*_epreinit_array [])(void) __attribute__((weak));
    extern void (*_sinit_array [])(void) __attribute__((weak));
    extern void (*_einit_array [])(void) __attribute__((weak));
    extern int main();

    for(uint8_t* i = _sdata; i <= _edata; i++, p++){
        *i = *p;
    }
    for(uint8_t* i = _sbss; i <= _ebss; i++){
        *i = 0;
    }
    for(void (**i)() = _spreinit_array; i <= _epreinit_array; i++){
        (**i)();
    }
    for(void (**i)() = _sinit_array; i <= _einit_array; i++){
        (**i)();
    }

    main();
}