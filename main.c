#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <unistd.h>
#include "constants.h"
#include "getopt.h"
#include "plot_functions.h"

void draw_x_axis(int width, int height);
void draw_y_axis(int width, int height);

int main(int argc, char *argv[])
{
  plot_fn_t plot_fn = extract_getopt_plot_function(argc, argv);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Function Plotter"); 
  SetTargetFPS(240);

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


