#pragma once
#include "piece.hpp"
#include <array>

class Game {
public:
  Game();
  ~Game();

  bool inspectState();
  void movePiece(char c);
  void setPiece(PieceGrid);

private:
  std::array<std::array<bool, 10>, 24> board;
  Piece piece;
  bool gameOver;
};