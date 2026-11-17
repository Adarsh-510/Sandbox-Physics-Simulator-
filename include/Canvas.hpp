#pragma once
#include <memory>
#include <vector>
#include "Material.hpp"

using namespace std;

class Canvas {
 public:
  int width, height;

  Canvas(int width, int height) : width(width), height(height) {
    canvas_matrix.resize(width * height);
  }

  bool in_canvas(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
  }
  bool in_canvas(Position position) const {
    return in_canvas(position.x, position.y);
  }

  void set(int x, int y, unique_ptr<Material> material) {
    if (in_canvas(x, y))
      canvas_matrix[index(x, y)] = std::move(material);
  }
  void set(Position position, unique_ptr<Material> material) {
    set(position.x, position.y, std::move(material));
  }

  void clear(int x, int y) { set(x, y, nullptr); }
  void clear(Position position) { set(position, nullptr); }

  void swap(Position position1, Position position2) {
    if (in_canvas(position1) && in_canvas(position2)) {
      std::swap(canvas_matrix[index(position1)],
                canvas_matrix[index(position2)]);
    }
  }

  Material* get(int x, int y) const {
    if (!in_canvas(x, y))
      return nullptr;
    return canvas_matrix[index(x, y)].get();
  }
  Material* get(Position position) const { return get(position.x, position.y); }

  bool is_empty(int x, int y) const {
    if (!in_canvas(x, y))
      return false;
    return get(x, y) == nullptr;
  }
  bool is_empty(Position position) const { return is_empty(position.x, position.y); }

  void update_canvas() {
    prepare_matrix();
    bool left_to_right = frame_flip;
    for (int y = height - 1; y >= 0; y--) {
      if (left_to_right) {
        for (int x = 0; x < width; x++) {
          Material* material = get(x, y);
          if (material && !material->updated)
            material->update(Position(x, y), *this);
        }
      } else {
        for (int x = width - 1; x >= 0; x--) {
          Material* material = get(x, y);
          if (material && !material->updated)
            material->update(Position(x, y), *this);
        }
      }
      left_to_right = !left_to_right;
    }
    frame_flip = !frame_flip;
  }

  void prepare_matrix() {
    for (auto& pixel : canvas_matrix)
      if (pixel)
        pixel->updated = false;
  }

 private:
  vector<unique_ptr<Material>> canvas_matrix;
  bool frame_flip = true;

  int index(int x, int y) const { return y * width + x; }
  int index(Position position) const { return index(position.x, position.y); }
};
