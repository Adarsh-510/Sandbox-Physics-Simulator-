#include <random>
#include "Canvas.hpp"
#include "Material.hpp"

using namespace std;

static mt19937 rng(random_device{}());
static uniform_int_distribution<int> coin_flip(0, 1);
static uniform_int_distribution<int> move_chance(0, 3);

bool Material::can_swap(Position position, Canvas& canvas) {
  if (!canvas.in_canvas(position))
    return false;
  if (canvas.is_empty(position))
    return true;

  return this->ID < canvas.get(position)->ID;
}

// falling blocks
void Falling::update(Position position, Canvas& canvas) {
  updated = true;

  if (can_swap(position.below(), canvas)) {
    canvas.swap(position, position.below());
    return;
  }

  bool left_first = coin_flip(rng);
  Position first  = left_first ? position.below().left() : position.below().right();
  Position second = left_first ? position.below().right() : position.below().left();

  if (can_swap(first, canvas)) {
    canvas.swap(position, first);
    return;
  }
  if (can_swap(second, canvas)) {
    canvas.swap(position, second);
    return;
  }
}

// liquids
void Liquid::update(Position position, Canvas& canvas) {
  updated = true;

  if (can_swap(position.below(), canvas)) {
    canvas.swap(position, position.below());
    return;
  }

  bool left_first = coin_flip(rng);
  Position first  = left_first ? position.below().left() : position.below().right();
  Position second = left_first ? position.below().right() : position.below().left();

  if (can_swap(first, canvas)) {
    canvas.swap(position, first);
    return;
  }
  if (can_swap(second, canvas)) {
    canvas.swap(position, second);
    return;
  }

  first  = left_first ? position.left() : position.right();
  second = left_first ? position.right() : position.left();

  if (can_swap(first, canvas)) {
    canvas.swap(position, first);
    return;
  }
  if (can_swap(second, canvas)) {
    canvas.swap(position, second);
    return;
  }
}

// gases
void Gas::update(Position position, Canvas& canvas) {
  updated = true;

  if (move_chance(rng) == 0)
    return;

  if (can_swap(position.above(), canvas)) {
    canvas.swap(position, position.above());
    return;
  }

  bool left_first = coin_flip(rng);
  Position first  = left_first ? position.above().left() : position.above().right();
  Position second = left_first ? position.above().right() : position.above().left();

  if (can_swap(first, canvas)) {
    canvas.swap(position, first);
    return;
  }
  if (can_swap(second, canvas)) {
    canvas.swap(position, second);
    return;
  }

  first  = left_first ? position.left() : position.right();
  second = left_first ? position.right() : position.left();

  if (can_swap(first, canvas)) {
    canvas.swap(position, first);
    return;
  }
  if (can_swap(second, canvas)) {
    canvas.swap(position, second);
    return;
  }
}
