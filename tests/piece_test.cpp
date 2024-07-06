#include "piece.hpp"
#include "pieceGrid.hpp"
#include <gtest/gtest.h>

TEST(PIECE_TEST, piece_offset_ok) {
  Piece piece;
  piece.setPosition({0, 0});

  // create grid
  PieceGrid pg(std::array<std::array<bool, 3>, 3>{
      std::array<bool, 3>{false, false, false},
      std::array<bool, 3>{false, true, false},
      std::array<bool, 3>{false, false, false}});

  piece.setPieceGrid(pg);

  // nothing
  piece.offset('u');

  // check the position
  ASSERT_EQ(piece.getPosition().first, 0);
  ASSERT_EQ(piece.getPosition().second, 0);

  // down
  piece.setPosition({0, 0});
  piece.offset('d');

  // check the position
  ASSERT_EQ(piece.getPosition().first, 1);
  ASSERT_EQ(piece.getPosition().second, 0);

  // right
  piece.setPosition({0, 0});
  piece.offset('r');

  // check the position
  ASSERT_EQ(piece.getPosition().first, 0);
  ASSERT_EQ(piece.getPosition().second, 1);

  // left
  piece.setPosition({0, 0});
  piece.offset('l');

  // check the position
  ASSERT_EQ(piece.getPosition().first, 0);
  ASSERT_EQ(piece.getPosition().second, -1);

  // random letter
  piece.setPosition({0, 0});
  piece.offset('z');

  // check the position
  ASSERT_EQ(piece.getPosition().first, 0);
  ASSERT_EQ(piece.getPosition().second, 0);
}

TEST(PIECE_TEST, piece_offset_out_of_bounds_ok) {
  Piece piece;
  piece.setPosition({22, 0});

  // create grid
  PieceGrid pg(std::array<std::array<bool, 3>, 3>{
      std::array<bool, 3>{false, false, false},
      std::array<bool, 3>{true, true, true},
      std::array<bool, 3>{false, false, false}});

  piece.setPieceGrid(pg);

  // down offset should do nothing
  piece.offset('d');

  // check the position
  ASSERT_EQ(piece.getPosition().first, 22);
  ASSERT_EQ(piece.getPosition().second, 0);

  // change the position to {0, 0} and check that left offset does not do shit
  piece.setPosition({0, 0});
  piece.offset('l');

  // check the position
  ASSERT_EQ(piece.getPosition().first, 0);
  ASSERT_EQ(piece.getPosition().second, 0);

  // change the position to {7, 0} and check that left offset does not do shit
  piece.setPosition({0, 7});
  piece.offset('r');

  // check the position
  ASSERT_EQ(piece.getPosition().first, 0);
  ASSERT_EQ(piece.getPosition().second, 7);
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

TEST(PIECE_TEST, piece_upper_pts_ok) {
  Piece piece;
  piece.setPosition({1, 1});

  // create grid
  PieceGrid pg(std::array<std::array<bool, 3>, 3>{
      std::array<bool, 3>{false, true, true},
      std::array<bool, 3>{false, true, false},
      std::array<bool, 3>{false, true, true}});

  piece.setPieceGrid(pg);
  std::vector<std::pair<int, int>> upperPoints = piece.getUpperPoints();

  // assert the upper points are only  2
  ASSERT_EQ(upperPoints.size(), 2);

  // assert the positions of the upperPoints
  for (std::pair<int, int> pos :
       std::vector<std::pair<int, int>>{{1, 2}, {1, 3}}) {
    auto it = std::find(upperPoints.begin(), upperPoints.end(), pos);
    ASSERT_TRUE(it != upperPoints.end());
  }
}

TEST(PIECE_TEST, piece_rightmost_pts_ok) {
  Piece piece;
  piece.setPosition({1, 1});

  // create grid
  PieceGrid pg(std::array<std::array<bool, 3>, 3>{
      std::array<bool, 3>{false, true, true},
      std::array<bool, 3>{false, true, false},
      std::array<bool, 3>{false, true, true}});

  piece.setPieceGrid(pg);
  std::vector<std::pair<int, int>> rightmostPoints = piece.getRightmostPoints();

  // assert the lower points are only  2
  ASSERT_EQ(rightmostPoints.size(), 2);

  // assert the positions of the rightmostPoints
  for (std::pair<int, int> pos :
       std::vector<std::pair<int, int>>{{1, 3}, {3, 3}}) {
    auto it = std::find(rightmostPoints.begin(), rightmostPoints.end(), pos);
    ASSERT_TRUE(it != rightmostPoints.end());
  }
}

TEST(PIECE_TEST, piece_leftmost_pts_ok) {
  Piece piece;
  piece.setPosition({1, 1});

  // create grid
  PieceGrid pg(std::array<std::array<bool, 3>, 3>{
      std::array<bool, 3>{true, true, false},
      std::array<bool, 3>{false, true, false},
      std::array<bool, 3>{true, true, false}});

  piece.setPieceGrid(pg);
  std::vector<std::pair<int, int>> leftmostPoints = piece.getLeftmostPoints();

  // assert the lower points are only  2
  ASSERT_EQ(leftmostPoints.size(), 2);

  // assert the positions of the leftmostPoints
  for (std::pair<int, int> pos :
       std::vector<std::pair<int, int>>{{1, 1}, {3, 1}}) {
    auto it = std::find(leftmostPoints.begin(), leftmostPoints.end(), pos);
    ASSERT_TRUE(it != leftmostPoints.end());
  }
}