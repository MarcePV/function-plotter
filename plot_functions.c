#include "constants.h"
#include "plot_functions.h"
#include <math.h>

float plot_parabola(float x, float x_scale, float y_scale)
{
  return pow(x * x_scale, 2) * y_scale;
}
float plot_sin(float x, float x_scale, float y_scale)
{
  return sinf(x * x_scale) * y_scale;
}
float plot_e(float x, float x_scale, float y_scale)
{
  return pow(EULER, x * x_scale) * y_scale;
}
