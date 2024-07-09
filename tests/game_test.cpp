#include "game.hpp"
#include <gtest/gtest.h>

TEST(GAME_TEST, game_ok) {

  // construct a game
  Game g;
  ASSERT_EQ(g.isGameOver(), false);
  ASSERT_TRUE(g.getPiece().getUpperPoints().size() != 0);
  ASSERT_TRUE(g.getPiece().getLowerPoints().size() != 0);
  ASSERT_TRUE(g.getPiece().getRightmostPoints().size() != 0);
  ASSERT_TRUE(g.getPiece().getLeftmostPoints().size() != 0);
}

TEST(GAME_TEST, piece_set_ok) {

  // construct a game
  Game g;

  int count = 0;
  while (count < 100 && !g.isPieceSet()) {
    count++;
    g.movePiece('d');
  }
  ASSERT_TRUE(count < 25);

  int secondCount = 0;
  g.pieceCycle('d', 0);

  while (secondCount < 100 && !g.isPieceSet()) {
    secondCount++;
    g.movePiece('d');
  }

  ASSERT_TRUE(secondCount < count);
}
