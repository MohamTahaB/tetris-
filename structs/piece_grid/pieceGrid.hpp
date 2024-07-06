#pragma once

#include <array>

class PieceGrid {
public:
  PieceGrid(std::array<std::array<bool, 3>, 3>);

  void rotate(int);
  std::array<std::array<bool, 3>, 3> getGrid();

private:
  std::array<std::array<bool, 3>, 3> grid;
};