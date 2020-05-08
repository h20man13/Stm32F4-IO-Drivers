#include "algebra.h"

static double log_helper(double input){
    return (input > 1) ? 1 + log_helper(input / 2) : 0;
}

uint32_t log(uint32_t input){
    return (uint32_t)log_helper((double)input);
}