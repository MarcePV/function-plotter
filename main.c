#include <math.h>
#include <raylib.h>
#include <raymath.h>

#define SCREEN_WIDTH 1440
#define SCREEN_HEIGHT 1440
#define CENTER_X SCREEN_WIDTH / 2.0f 
#define CENTER_Y SCREEN_HEIGHT / 2.0f 
 
void draw_x_axis(int width, int height);
void draw_y_axis(int width, int height);
float f(float x);

int main()
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Function Plotter"); 

  while (!WindowShouldClose())
  {
    

    BeginDrawing();

      ClearBackground(BLACK);

      for (float x = -CENTER_X; x < CENTER_X; x+= 0.05f)
      {
        float y = f(x);

        float pixelX = x + CENTER_X;
        float pixelY = CENTER_Y - y;

        DrawCircleV((Vector2){ pixelX, pixelY }, 1, BLUE);
      }

      draw_x_axis(SCREEN_WIDTH, SCREEN_HEIGHT);
      draw_y_axis(SCREEN_WIDTH, SCREEN_HEIGHT);

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

float f(float x)
{
  return pow(x, 3) / 1000.0f;
}
