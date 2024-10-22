#pragma once
#include "piece.hpp"
#include <array>

class Game {
public:
  Game();
  ~Game();

  bool isPieceSet();

  void pieceCycle(char, int);
  bool isPieceValid();
  void movePiece(char);
  void rotatePiece(int);

  void setPiece(PieceGrid);
  void resetBoard();
  void clearCompleteLines();

  std::array<std::array<bool, 10>, 24> getBoard();
  Piece getPiece();
  bool isGameOver();

  void debug();
  void launch();

private:
  int score;
  std::array<std::array<bool, 10>, 24> board;
  Piece piece;
  bool gameOver;
};