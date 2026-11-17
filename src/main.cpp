#define SDL_MAIN_HANDLED
#include <iostream>
#include "Canvas.hpp"
#include "Input.hpp"
#include "Renderer.hpp"

using namespace std;

int main() {
  const int targetFPS     = 60;
  const int cell_size     = 4;
  const int canvas_width  = 200;
  const int canvas_height = 150;

  cout << "Controls:\n";
  cout << "1: Sand\n";
  cout << "2: Water\n";
  cout << "3: Oil\n";
  cout << "4: Mercury\n";
  cout << "5: Smoke\n";
  cout << "6: Water Vapour\n";
  cout << "7: Stone\n";
  cout << "8: Wood\n";
  cout << "9: Snow\n";
  cout << "E: Erase\n";
  cout << "+/-: Change brush size\n";

  Canvas   canvas(canvas_width, canvas_height);
  Renderer renderer("Physics Simulator", canvas_width, canvas_height, cell_size);
  Input    input(cell_size);

  const Uint64 frame_delay = 1000 / targetFPS;

  bool running = true;
  while (running) {
    Uint64 frame_start = SDL_GetTicks();

    input.handle(canvas, running);
    canvas.update_canvas();
    renderer.render(canvas);

    Uint64 frame_time = SDL_GetTicks() - frame_start;
    if (frame_time < frame_delay) {
      SDL_Delay((Uint32)(frame_delay - frame_time));
    }
  }

  return 0;
}
