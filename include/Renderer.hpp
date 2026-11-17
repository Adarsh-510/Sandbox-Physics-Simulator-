#pragma once
#include <SDL3/SDL.h>
#include "Canvas.hpp"

class Renderer {
 public:
  Renderer(const char* title, int canvas_width, int canvas_height, int cell_size);
  ~Renderer();

  void render(const Canvas& canvas);

 private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  int cell_size;
};
