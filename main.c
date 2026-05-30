#include <math.h>
#include <raylib.h>
#include <raymath.h>

#define SCREEN_WIDTH 1440
#define SCREEN_HEIGHT 1440
#define CENTER_X SCREEN_WIDTH / 2.0f 
#define CENTER_Y SCREEN_HEIGHT / 2.0f 
#define ZOOM_FACTOR 1.5f; 
 
void draw_x_axis(int width, int height);
void draw_y_axis(int width, int height);
float f(float x, float x_scale, float y_scale);

int main()
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Function Plotter"); 

  float original_x_scale = 0.05f;
  float original_y_scale = 100.0f;

  float x_scale = original_x_scale;
  float y_scale = original_y_scale;

  float d_mouse_wheel = 0.0f;
  float percent_zoom = 0.0f;

  while (!WindowShouldClose())
  {
    d_mouse_wheel = GetMouseWheelMove();

    if (d_mouse_wheel > 0.0f) 
    {
      x_scale /= ZOOM_FACTOR;
      y_scale *= ZOOM_FACTOR;
    }
    else if (d_mouse_wheel < 0.0f)
    {
      x_scale *= ZOOM_FACTOR;
      y_scale /= ZOOM_FACTOR;
    }

    percent_zoom = (y_scale / original_y_scale) * 100.0f; 

    BeginDrawing();

      ClearBackground(BLACK);
      float previous_x, previous_y;
      bool first_point = true;

      for (float x = -CENTER_X; x < CENTER_X; x+= 15.0f)
      {
        float y = f(x, fabs(x_scale), fabs(y_scale));

        float pixelX = x + CENTER_X;
        float pixelY = CENTER_Y - y;

        DrawCircleV((Vector2){ pixelX, pixelY }, 1, BLUE);
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
      DrawText(TextFormat("Zoom: %.2f%%", percent_zoom), 100, 100, 75, GREEN);

    EndDrawing();
  }


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

float f(float x, float x_scale, float y_scale)
{
  //return sinf(x * x_scale) * y_scale;
  return pow(x * x_scale, 2) * y_scale;
  //return pow(2.71828, x * x_scale) * y_scale;
}
