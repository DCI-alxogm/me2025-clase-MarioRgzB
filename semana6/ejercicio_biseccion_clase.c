#include <stdio.h>
#include <math.h>

double f(double c) {
  if (c == 0.0) return -40.0;
  return ((9.8 * 68.1)/c)*(1 - exp(-c * 10.0 / 68.1)) - 40.0;
}