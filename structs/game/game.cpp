#include "game.hpp"

Game::Game()
    : piece(Piece()), board(std::array<std::array<bool, 10>, 24>{}),
      gameOver(false) {}

Game::~Game() { piece.~Piece(); }

void Game::setPiece(PieceGrid pg) {
  piece.setPieceGrid(pg);

  // TODO! add funcs to check the nax up, left, right most points to know how to
  // position the reference, which will be now simply <0,0>

  piece.setPosition({0, 0});
}

bool Game::inspectState() {}