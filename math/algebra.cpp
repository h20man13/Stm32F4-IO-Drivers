#include "algebra.h"

static uint32_t log_helper(uint32_t input){
    return (input > 1) ? 1 + log_helper(input / 2) : 0;
}

uint32_t log_2(uint32_t input){
    return (uint32_t)log_helper(input);
}