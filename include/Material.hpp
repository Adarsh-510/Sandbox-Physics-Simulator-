#pragma once
#include <SDL3/SDL.h>
#include <algorithm>
#include <random>
#include "Position.hpp"

using namespace std;

class Material {
 public:
  int ID = 0;
  SDL_Color pixel_color;
  bool updated = false;
  int color_variance = 8;

  Material(int ID, SDL_Color pixel_color, int color_variance = 8)
      : ID(ID), pixel_color(pixel_color), color_variance(color_variance) {
    randomize_color();
  }

  virtual ~Material() = default;

  virtual void update(Position position, class Canvas& canvas) = 0;

  bool can_swap(Position position, class Canvas& canvas);

 private:
  void randomize_color() {
    if (color_variance <= 0) return;
    static mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(-color_variance, color_variance);
    int offset = dist(rng);
    pixel_color.r = (Uint8)clamp((int)pixel_color.r + offset, 0, 255);
    pixel_color.g = (Uint8)clamp((int)pixel_color.g + offset, 0, 255);
    pixel_color.b = (Uint8)clamp((int)pixel_color.b + offset, 0, 255);
  }
};

class Falling : public Material {
 public:
  Falling(SDL_Color pixel_color, int color_variance = 8)
      : Material(10, pixel_color, color_variance) {}

  void update(Position position, Canvas& canvas) override;
};

class Liquid : public Material {
 public:
  int density_ID = 0;

  Liquid(SDL_Color pixel_color, int density_ID, int color_variance = 8)
      : Material(20, pixel_color, color_variance), density_ID(density_ID) {
    ID += 9 - density_ID;
  }

  void update(Position position, Canvas& canvas) override;
};

class Gas : public Material {
 public:
  int density_ID = 0;

  Gas(SDL_Color pixel_color, int density_ID, int color_variance = 8)
      : Material(30, pixel_color, color_variance), density_ID(density_ID) {
    ID += density_ID;
  }

  void update(Position position, Canvas& canvas) override;
};

class Stone : public Material {
 public:
  Stone() : Material(1, {150, 150, 150, 255}) {}

  void update(Position position, Canvas& canvas) override {}
};

class Wood : public Material {
 public:
  Wood() : Material(1, {133, 94, 66, 255}) {}

  void update(Position position, Canvas& canvas) override {}
};

class Sand : public Falling {
 public:
  Sand() : Falling({194, 178, 128, 255}) {}
};

class Snow : public Falling {
 public:
  Snow() : Falling({240, 248, 255, 255}) {}
};

class Water : public Liquid {
 public:
  Water() : Liquid({30, 100, 220, 255}, 5) {}
};

class Oil : public Liquid {
 public:
  Oil() : Liquid({180, 140, 20, 255}, 3) {}
};

class Mercury : public Liquid {
 public:
  Mercury() : Liquid({170, 175, 180, 255}, 8) {}
};

class Smoke : public Gas {
 public:
  Smoke() : Gas({90, 90, 90, 220}, 3) {}
};

class WaterVapour : public Gas {
 public:
  WaterVapour() : Gas({200, 215, 230, 180}, 1) {}
};
