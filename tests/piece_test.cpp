#include "piece.hpp"
#include "pieceGrid.hpp"
#include <gtest/gtest.h>

TEST(PIECE_TEST, piece_offset_ok) {
  Piece piece;
  piece.setPosition({0, 0});

  // create grid
  PieceGrid pg(std::array<std::array<bool, 3>, 3>{
      std::array<bool, 3>{false, false, false},
      std::array<bool, 3>{true, true, true},
      std::array<bool, 3>{false, false, false}});

  piece.setPieceGrid(pg);

  // up
  piece.offset('u');

  // check the position
  ASSERT_EQ(piece.getPosition().first, 1);
  ASSERT_EQ(piece.getPosition().second, 0);

  // down
  piece.offset('d');
  piece.offset('d');

  // check the position
  ASSERT_EQ(piece.getPosition().first, -1);
  ASSERT_EQ(piece.getPosition().second, 0);

  piece.offset('u');

  // right
  piece.offset('r');

  // check the position
  ASSERT_EQ(piece.getPosition().first, 0);
  ASSERT_EQ(piece.getPosition().second, 1);

  // left
  piece.offset('l');
  piece.offset('l');

  // check the position
  ASSERT_EQ(piece.getPosition().first, 0);
  ASSERT_EQ(piece.getPosition().second, -1);

  piece.offset('r');

  // random letter
  piece.offset('z');

  // check the position
  ASSERT_EQ(piece.getPosition().first, 0);
  ASSERT_EQ(piece.getPosition().second, 0);
}

TEST(PIECE_TEST, piece_cases_ok) {
  Piece piece;
  piece.setPosition({1, 1});

  // create grid
  PieceGrid pg(std::array<std::array<bool, 3>, 3>{
      std::array<bool, 3>{false, true, false},
      std::array<bool, 3>{false, true, false},
      std::array<bool, 3>{false, true, true}});

  piece.setPieceGrid(pg);
  std::vector<std::pair<int, int>> cases = piece.getCases();

  // assert the cases are only of size 4
  ASSERT_EQ(cases.size(), 4);

  // assert the positions of the cases
  for (std::pair<int, int> pos :
       std::vector<std::pair<int, int>>{{1, 2}, {2, 2}, {3, 2}, {3, 3}}) {
    auto it = std::find(cases.begin(), cases.end(), pos);
    ASSERT_TRUE(it != cases.end());
  }
}

TEST(PIECE_TEST, piece_lower_pts_ok) {
  Piece piece;
  piece.setPosition({1, 1});

  // create grid
  PieceGrid pg(std::array<std::array<bool, 3>, 3>{
      std::array<bool, 3>{false, true, false},
      std::array<bool, 3>{false, true, false},
      std::array<bool, 3>{false, true, true}});

  piece.setPieceGrid(pg);
  std::vector<std::pair<int, int>> lowerPoints = piece.getLowerPoints();

  // assert the lower points are only  2
  ASSERT_EQ(lowerPoints.size(), 2);

  // assert the positions of the lowerPoints
  for (std::pair<int, int> pos :
       std::vector<std::pair<int, int>>{{3, 2}, {3, 3}}) {
    auto it = std::find(lowerPoints.begin(), lowerPoints.end(), pos);
    ASSERT_TRUE(it != lowerPoints.end());
  }
}