#include "pieceGrid.hpp"
#include <gtest/gtest.h>

TEST(PIECE_GRID_TEST, piece_grid_rotation_ok) {

  // create grid
  PieceGrid pg(std::array<std::array<bool, 3>, 3>{
      std::array<bool, 3>{true, false, false},
      std::array<bool, 3>{false, true, false},
      std::array<bool, 3>{false, true, false}});

  // first rotation
  pg.rotate(1);

  // check the grid
  std::array<std::array<bool, 3>, 3> grid;
  int posNumber = 0;

  grid = pg.getGrid();
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      posNumber += (grid[i][j] ? 1 : 0);
    }
  }

  ASSERT_EQ(posNumber, 3);

  // check the positions of checked cases
  ASSERT_TRUE(grid[1][1]);
  ASSERT_TRUE(grid[0][2]);
  ASSERT_TRUE(grid[1][0]);

  // reset rotation (three quarters)
  pg.rotate(3);

  // check
  posNumber = 0;
  grid = pg.getGrid();

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      posNumber += (grid[i][j] ? 1 : 0);
    }
  }

  ASSERT_EQ(posNumber, 3);

  // check the positions of checked cases
  ASSERT_TRUE(grid[1][1]);
  ASSERT_TRUE(grid[0][0]);
  ASSERT_TRUE(grid[2][1]);

  // U turn rotation
  pg.rotate(2);

  // check
  posNumber = 0;
  grid = pg.getGrid();

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      posNumber += (grid[i][j] ? 1 : 0);
    }
  }

  ASSERT_EQ(posNumber, 3);

  // check the positions of checked cases
  ASSERT_TRUE(grid[1][1]);
  ASSERT_TRUE(grid[2][2]);
  ASSERT_TRUE(grid[0][1]);
}