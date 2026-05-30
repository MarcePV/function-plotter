#include "getopt.h"

plot_fn_t extract_getopt_plot_function(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("\n\nUsage: <program> [-f] <name of function> (e.g. parabola, euler, sin).\n\n");
    CloseWindow();
    exit(-1);
  }

  char opt;
  char *func_name;

  while ( (opt = getopt(argc, argv, "f:")) != -1)
  {
    switch (opt)
    {
      case 'f':
        func_name = optarg;  
        break;
      default:
        printf("\n\nOptarg Usage: <program> [-f] <name of function> (e.g. parabola, euler, sin).\n\n");
        CloseWindow();
        exit(-1);
    }
  }

  if (strcmp(func_name, "parabola") == 0)
  {
    return plot_parabola;
  }
  else if (strcmp(func_name, "euler") == 0)
  {
    return plot_e;
  } 
  else if (strcmp(func_name, "sin") == 0)
  {
    return plot_sin;
  }

  return NULL;
}
