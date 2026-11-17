#include "Renderer.hpp"

Renderer::Renderer(const char* title, int canvas_width, int canvas_height, int cell_size)
    : cell_size(cell_size) {
  SDL_Init(SDL_INIT_VIDEO);
  window   = SDL_CreateWindow(title, canvas_width * cell_size, canvas_height * cell_size, 0);
  renderer = SDL_CreateRenderer(window, nullptr);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

Renderer::~Renderer() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Renderer::render(const Canvas& canvas) {
  SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);
  SDL_RenderClear(renderer);

  for (int y = 0; y < canvas.height; y++) {
    for (int x = 0; x < canvas.width; x++) {
      Material* mat = canvas.get(x, y);
      if (!mat) continue;

      SDL_SetRenderDrawColor(renderer,
        mat->pixel_color.r,
        mat->pixel_color.g,
        mat->pixel_color.b,
        mat->pixel_color.a);

      SDL_FRect rect = {
        (float)(x * cell_size),
        (float)(y * cell_size),
        (float)cell_size,
        (float)cell_size
      };
      SDL_RenderFillRect(renderer, &rect);
    }
  }

  SDL_RenderPresent(renderer);
}
