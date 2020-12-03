#include "algebra.h"

static double log_helper(double input){
    return (input > 1) ? 1 + log_helper(input / 2) : 0;
}

double log_2(double input){
    return log_helper(input);
}

double map(double val, double curMin, double curMax, double toMin, double toMax){
  return toMin + ((toMax - toMin)/(curMax - curMin)) * (val - curMin);
}
