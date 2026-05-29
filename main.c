#include <raylib.h>
#include <raymath.h>

#define SCREEN_WIDTH 1440
#define SCREEN_HEIGHT 1440 // for now, transform for asymetric alter
 
void draw_x_axis(int width, int height);
void draw_y_axis(int width, int height);
int f(float x);

int main()
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Function Plotter"); 

  while (!WindowShouldClose())
  {
    

    BeginDrawing();
      ClearBackground(BLACK);

      for (float x = 0.0f; x < SCREEN_WIDTH; x++)
      {
        DrawCircle(x, f(x), 1, BLUE);
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

int f(float x)
{
  return x;
}
