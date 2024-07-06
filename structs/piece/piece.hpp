#pragma once

#include "pieceGrid.hpp"
#include <vector>

class Piece {
public:
  Piece();
  ~Piece();

  void offset(char);
  void rotate(int);
  std::vector<std::pair<int, int>> getCases();
  std::vector<std::pair<int, int>> getLowerPoints();
  std::vector<std::pair<int, int>> getUpperPoints();
  std::vector<std::pair<int, int>> getRightmostPoints();
  std::vector<std::pair<int, int>> getLeftmostPoints();
  void setPieceGrid(PieceGrid pieceGrid);
  void setPosition(std::pair<int, int> newPos);
  std::pair<int, int> getPosition();

private:
  PieceGrid pieceGrid;
  std::pair<int, int> position;
};