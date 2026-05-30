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
  SetTargetFPS(1000);

  float original_x_scale = 0.05f;
  float original_y_scale = 100.0f;

  float x_scale = original_x_scale;
  float y_scale = original_y_scale;

  float d_mouse_wheel = ZERO_SCROLL;

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

      Vector2 points[MAX_POINTS] = {0};
      int point_count = 0;

      float start_x = -CENTER_X - pixel_offset.x; 
      float end_x = start_x + SCREEN_WIDTH;

      for (float x = start_x; x < end_x && point_count < MAX_POINTS; x+= DELTA_PIXELS)
      {
        float y = plot_fn(x, fabs(x_scale), fabs(y_scale)); // arbitrary plot for now

        float pixelX = x + CENTER_X + pixel_offset.x;
        float pixelY = CENTER_Y - y + pixel_offset.y;

        points[point_count].x = pixelX; 
        points[point_count].y = pixelY; 
        point_count++;

      }

      DrawLineStrip(points, point_count, BLUE);
      draw_x_axis(SCREEN_WIDTH, SCREEN_HEIGHT, pixel_offset);
      draw_y_axis(SCREEN_WIDTH, SCREEN_HEIGHT, pixel_offset);

      DrawText(TextFormat("FPS: %.2f", 1.0f / GetFrameTime()), FPS_TEXT_X, FPS_TEXT_Y, TEXT_FONT_SIZE, GREEN);
      DrawText("x", SCREEN_WIDTH - 50, SCREEN_HEIGHT / 2 + (int)pixel_offset.y, 30, WHITE);
      DrawText("y", SCREEN_WIDTH / 2 + 10 + (int) pixel_offset.x, 0, 30, WHITE);

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


