#include "pieceGrid.hpp"
#include <map>

PieceGrid::PieceGrid(std::array<std::array<bool, 3>, 3> init) {
  grid = init;
  return;
}

void singleRotation(std::array<std::array<bool, 3>, 3> &grid) {
  std::array<std::array<bool, 3>, 3> aux;
  std::map<std::pair<int, int>, std::pair<int, int>> rotationMap = {
      {{0, 0}, {0, 2}}, {{0, 2}, {2, 2}}, {{2, 2}, {2, 0}},
      {{2, 0}, {0, 0}}, {{0, 1}, {1, 2}}, {{1, 2}, {2, 1}},
      {{2, 1}, {1, 0}}, {{1, 0}, {0, 1}}, {{1, 1}, {1, 1}}};

  std::pair<int, int> newPos;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      newPos = rotationMap[{i, j}];
      aux[newPos.first][newPos.second] = grid[i][j];
    }
  }

  // edit the grid
  grid = aux;
  return;
}

void PieceGrid::rotate(int rotation) {
  rotation %= 4;
  while (rotation--) {
    singleRotation(grid);
  }
  return;
}

std::array<std::array<bool, 3>, 3> PieceGrid::getGrid() { return grid; }