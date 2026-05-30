#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "constants.h"
#include "plot_functions.h"

void draw_x_axis(int width, int height);
void draw_y_axis(int width, int height);

int main(int argc, char *argv[])
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Function Plotter"); 
  SetTargetFPS(240);

  if (argc < 2)
  {
    printf("\n\nUsage: <program> [-f] <name of function> (e.g. parabola, euler, sin).\n\n");
    CloseWindow();
    return -1;
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
        return -1;
    }
  }

  if (strcmp(func_name, "parabola") == 0)
  {
    plot_fn = plot_parabola;
  }
  else if (strcmp(func_name, "euler") == 0)
  {
    plot_fn = plot_e;
  } 
  else if (strcmp(func_name, "sin") == 0)
  {
    plot_fn = plot_sin;
  }

  printf("\n\n%s\n\n", func_name);

  

  float original_x_scale = 0.05f;
  float original_y_scale = 100.0f;

  float x_scale = original_x_scale;
  float y_scale = original_y_scale;

  float d_mouse_wheel = ZERO_SCROLL;
  float percent_zoom = 0.0f;

  while (!WindowShouldClose())
  {
    d_mouse_wheel = GetMouseWheelMove();

    if (d_mouse_wheel > ZERO_SCROLL) 
    {
      x_scale /= ZOOM_FACTOR;
      y_scale *= ZOOM_FACTOR;
    }
    else if (d_mouse_wheel < ZERO_SCROLL)
    {
      x_scale *= ZOOM_FACTOR;
      y_scale /= ZOOM_FACTOR;
    }

    percent_zoom = (y_scale / original_y_scale) * PERCENT_100; 

    BeginDrawing();

      ClearBackground(BLACK);
      float previous_x, previous_y;
      bool first_point = true;

      for (float x = -CENTER_X; x < CENTER_X; x+= DELTA_PIXELS)
      {
        float y = plot_fn(x, fabs(x_scale), fabs(y_scale)); // arbitrary plot for now

        float pixelX = x + CENTER_X;
        float pixelY = CENTER_Y - y;

        DrawCircleV((Vector2){ pixelX, pixelY }, POINT_RADIUS, BLUE);
        if (!first_point) 
        {
          DrawLine(previous_x, previous_y, pixelX, pixelY, BLUE);
        }
        
        previous_x = pixelX;
        previous_y = pixelY;
        first_point = false;
      }

      draw_x_axis(SCREEN_WIDTH, SCREEN_HEIGHT);
      draw_y_axis(SCREEN_WIDTH, SCREEN_HEIGHT);

      DrawText(TextFormat("Zoom: %.2f%%", percent_zoom), ZOOM_PERCENT_TEXT_X, ZOOM_PERCENT_TEXT_Y, TEXT_FONT_SIZE, GREEN);
      DrawText(TextFormat("FPS: %.2f", 1.0f / GetFrameTime()), FPS_TEXT_X, FPS_TEXT_Y, TEXT_FONT_SIZE, GREEN);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}


void draw_x_axis(int width, int height)
{
  DrawLine(width / 2, 0, width / 2, height, WHITE);  
}

void draw_y_axis(int width, int height)
{
  DrawLine(0, height / 2, width, height / 2, WHITE);
}

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
