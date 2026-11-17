#pragma once
#include <SDL3/SDL.h>
#include <algorithm>
#include <memory>
#include "Canvas.hpp"
#include "Material.hpp"

using namespace std;

enum class MaterialType {
  Sand,
  Water,
  Oil,
  Mercury,
  Smoke,
  WaterVapour,
  Stone,
  Wood,
  Snow,
  Erase
};

class Input {
 public:
  MaterialType selected = MaterialType::Sand;
  int brush_size = 3;

  Input(int cell_size) : cell_size(cell_size) {}

  void handle(Canvas& canvas, bool& running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_EVENT_QUIT:
          running = false;
          break;

        case SDL_EVENT_KEY_DOWN:
          switch (event.key.scancode) {
            case SDL_SCANCODE_1:
              selected = MaterialType::Sand;
              break;
            case SDL_SCANCODE_2:
              selected = MaterialType::Water;
              break;
            case SDL_SCANCODE_3:
              selected = MaterialType::Oil;
              break;
            case SDL_SCANCODE_4:
              selected = MaterialType::Mercury;
              break;
            case SDL_SCANCODE_5:
              selected = MaterialType::Smoke;
              break;
            case SDL_SCANCODE_6:
              selected = MaterialType::WaterVapour;
              break;
            case SDL_SCANCODE_7:
              selected = MaterialType::Stone;
              break;
            case SDL_SCANCODE_8:
              selected = MaterialType::Wood;
              break;
            case SDL_SCANCODE_9:
              selected = MaterialType::Snow;
              break;
            case SDL_SCANCODE_E:
              selected = MaterialType::Erase;
              break;
            case SDL_SCANCODE_EQUALS:
            case SDL_SCANCODE_KP_PLUS:
              brush_size = min(brush_size + 1, 15);
              break;
            case SDL_SCANCODE_MINUS:
            case SDL_SCANCODE_KP_MINUS:
              brush_size = max(brush_size - 1, 1);
              break;
            default:
              break;
          }
          break;
      }
    }

    float mx, my;
    SDL_MouseButtonFlags buttons = SDL_GetMouseState(&mx, &my);

    int cx = (int)(mx / cell_size);
    int cy = (int)(my / cell_size);

    if (buttons & SDL_BUTTON_LMASK) {
      if (selected == MaterialType::Erase)
        erase(canvas, cx, cy);
      else
        place(canvas, cx, cy);
    }

    if (buttons & SDL_BUTTON_RMASK)
      erase(canvas, cx, cy);
  }

 private:
  int cell_size;

  void place(Canvas& canvas, int cx, int cy) {
    int r = brush_size;
    for (int dy = -r; dy <= r; dy++) {
      for (int dx = -r; dx <= r; dx++) {
        if (dx * dx + dy * dy > r * r)
          continue;

        int x = cx + dx;
        int y = cy + dy;
        if (!canvas.in_canvas(x, y) || !canvas.is_empty(x, y))
          continue;

        unique_ptr<Material> mat;
        switch (selected) {
          case MaterialType::Sand:
            mat = make_unique<Sand>();
            break;
          case MaterialType::Water:
            mat = make_unique<Water>();
            break;
          case MaterialType::Oil:
            mat = make_unique<Oil>();
            break;
          case MaterialType::Mercury:
            mat = make_unique<Mercury>();
            break;
          case MaterialType::Smoke:
            mat = make_unique<Smoke>();
            break;
          case MaterialType::WaterVapour:
            mat = make_unique<WaterVapour>();
            break;
          case MaterialType::Stone:
            mat = make_unique<Stone>();
            break;
          case MaterialType::Wood:
            mat = make_unique<Wood>();
            break;
          case MaterialType::Snow:
            mat = make_unique<Snow>();
            break;
          default:
            break;
        }

        if (mat)
          canvas.set(x, y, std::move(mat));
      }
    }
  }

  void erase(Canvas& canvas, int cx, int cy) {
    int r = brush_size;
    for (int dy = -r; dy <= r; dy++)
      for (int dx = -r; dx <= r; dx++)
        if (dx * dx + dy * dy <= r * r)
          canvas.clear(cx + dx, cy + dy);
  }
};
