#ifndef TIMER_SRC
#define TIMER_SRC

#include <stdint.h>

typedef uint32_t src_val;

src_val SYS_CLK_MUX;
src_val PLL_SRC_MUX;

const src_val HSI = 16000000;
const src_val HSE = 8000000;
const src_val LSI = 32000;

void Change_SYS_SRC(src_val);
void Change_PLL_MUX(src_val);

#endif
