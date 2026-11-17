#pragma once

class Position {
 public:
  int x, y;

  Position(int x = 0, int y = 0) : x(x), y(y) {}

  Position above() const { return Position(x, y - 1); }
  Position below() const { return Position(x, y + 1); }
  Position right() const { return Position(x + 1, y); }
  Position left()  const { return Position(x - 1, y); }

  bool operator==(const Position& operand) const {
    return x == operand.x && y == operand.y;
  }

  bool operator!=(const Position& operand) const { return !(*this == operand); }

  Position& operator+=(const Position& operand) {
    x += operand.x;
    y += operand.y;
    return *this;
  }
};
