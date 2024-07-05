#pragma once

class PieceGrid {
public:
  PieceGrid();
  ~PieceGrid();

  void rotate(int);
  bool **getGrid();

private:
  bool grid[3][3];
};