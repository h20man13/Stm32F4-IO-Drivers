#ifndef TIMER_SRC
#define TIMER_SRC

#include <stdint.h>

typedef uint32_t src_val;

const src_val HSI = 16000000;
const src_val HSE = 8000000;
const src_val LSI = 32000;

src_val get_SYS_SRC();
src_val get_PLL_MUX();

void Change_SYS_SRC(src_val);
void Change_PLL_MUX(src_val);

#endif
