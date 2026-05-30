#ifndef PLOT_FUNCTIONS_H
#define PLOT_FUNCTIONS_H

#include <stdlib.h>

float plot_parabola(float x, float x_scale, float y_scale);
float plot_sin(float x, float x_scale, float y_scale);
float plot_e(float x, float x_scale, float y_scale);
extern float (*plot_fn)(float, float, float);

#endif
