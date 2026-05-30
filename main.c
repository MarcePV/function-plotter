#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <unistd.h>
#include "constants.h"
#include "getopt.h"
#include "plot_functions.h"

void draw_x_axis(int width, int height, Vector2 pixel_offset);
void draw_y_axis(int width, int height, Vector2 pixel_offset);

int main(int argc, char *argv[])
{
  plot_fn_t plot_fn = extract_getopt_plot_function(argc, argv);
  
  if (plot_fn == NULL) return 1;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Function Plotter"); 
  SetTargetFPS(240);

  float original_x_scale = 0.05f;
  float original_y_scale = 100.0f;

  float x_scale = original_x_scale;
  float y_scale = original_y_scale;

  float d_mouse_wheel = ZERO_SCROLL;
  float percent_zoom = 0.0f;

  Vector2 pixel_offset = Vector2Zero();

  bool dragging = false;

  while (!WindowShouldClose())
  {
    // calculate zoom 
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

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !dragging)
    {
      dragging = true;
    }
    else if (!IsMouseButtonDown(MOUSE_LEFT_BUTTON) && dragging)
    {
      dragging = false;
    }

    if (dragging)
    {
      pixel_offset = Vector2Add(pixel_offset, GetMouseDelta()); 
    }

    BeginDrawing();

      ClearBackground(BLACK);
      float previous_x, previous_y;
      bool first_point = true;

      for (float x = -CENTER_X - pixel_offset.x; x < CENTER_X - pixel_offset.x; x+= DELTA_PIXELS)
      {
        float y = plot_fn(x, fabs(x_scale), fabs(y_scale)); // arbitrary plot for now

        float pixelX = x + CENTER_X + pixel_offset.x;
        float pixelY = CENTER_Y - y + pixel_offset.y;

        DrawCircleV((Vector2){ pixelX, pixelY }, POINT_RADIUS, BLUE);
        if (!first_point) 
        {
          DrawLine(previous_x, previous_y, (int) pixelX, (int) pixelY, BLUE);
        }
        
        previous_x = pixelX;
        previous_y = pixelY;
        first_point = false;
      }

      draw_x_axis(SCREEN_WIDTH, SCREEN_HEIGHT, pixel_offset);
      draw_y_axis(SCREEN_WIDTH, SCREEN_HEIGHT, pixel_offset);

      DrawText(TextFormat("Zoom: %.2f%%", percent_zoom), ZOOM_PERCENT_TEXT_X, ZOOM_PERCENT_TEXT_Y, TEXT_FONT_SIZE, GREEN);
      DrawText(TextFormat("FPS: %.2f", 1.0f / GetFrameTime()), FPS_TEXT_X, FPS_TEXT_Y, TEXT_FONT_SIZE, GREEN);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}


void draw_y_axis(int width, int height, Vector2 pixel_offset)
{
  DrawLine(width / 2.0f + pixel_offset.x, 0, width / 2.0f + pixel_offset.x, height, WHITE);  
}

void draw_x_axis(int width, int height, Vector2 pixel_offset)
{
  DrawLine(0, height / 2.0f + pixel_offset.y, width, height / 2.0f + pixel_offset.y, WHITE);
}


