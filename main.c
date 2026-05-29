#include <raylib.h>
#include <raymath.h>

void draw_x_axis(int width, int height);
void draw_y_axis(int width, int height);

int main()
{
  const int screen_width = 1920;
  const int screen_height = 1080;

  InitWindow(screen_width, screen_height, "Function Plotter"); 

  while (!WindowShouldClose())
  {
    

    BeginDrawing();
      ClearBackground(BLACK);

      draw_x_axis(screen_width, screen_height);
      draw_y_axis(screen_width, screen_height);

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
