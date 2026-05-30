Desmos-like function plotter in Raylib C
Shows FPS and can take any function.
Avg FPS on my machine = 600 FPS
Uses DrawLineStrip() to buffer ```2000``` points on the screen at once.

How To Use:
----------
```./my-app -f <name-of-function> (parabola, euler, and sin are provided)```
You can add your own functions by adding your own function in the source code and then editing the getopts (using C-style function pointers)
You can zoom in with the ```scroll wheel``` and you can also move the graph around with ```left mouse button```



TODO additional functionality:
-----------------------------
- UX buttons like return to center for example.
