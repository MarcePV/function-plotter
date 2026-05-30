#ifndef GETOPT_H
#define GETOPT_H

#include <unistd.h>
#include <string.h>
#include "plot_functions.h"
#include <raylib.h>
#include <stdio.h>

plot_fn_t extract_getopt_plot_function(int argc, char *argv[]);
#endif
