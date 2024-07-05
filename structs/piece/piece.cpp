#include "piece.hpp"
#include <map>
#include <vector>

void Piece::rotate(int rotation) { pieceGrid.rotate(rotation); }

void Piece::offset(char c) {
  // map the chars to offsets
  std::map<char, std::pair<int, int>> offsetVals = {
      {'u', {1, .0}}, {'d', {-1, 0}}, {'l', {0, -1}}, {'r', {0, 1}}};

  // update the position
  // This op should not be done unless the move is possible,
  // this is verified in the game level.
  position.first += offsetVals[c].first;
  position.second += offsetVals[c].second;

  return;
}

std::vector<std::pair<int, int>> Piece::getCases() {
  std::vector<std::pair<int, int>> pieces;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (pieceGrid.getGrid()[i + position.first][j + position.second]) {
        pieces.push_back({i + position.first, j + position.second});
      }
    }
  }

  return pieces;
}

std::vector<std::pair<int, int>> Piece::getLowerPoints() {
  std::vector<std::pair<int, int>> lowerPointsCoords;

  for (int j = 2; j >= 0; j--) {
    bool found = false;
    for (int i = 0; i < 3; i++) {
      if (pieceGrid.getGrid()[i][j]) {
        found = true;
        lowerPointsCoords.push_back({i + position.first, j + position.second});
      }
    }

    if (found) {
      break;
    }
  }

  return lowerPointsCoords;
}

void Piece::setPieceGrid(PieceGrid pg) { pieceGrid = pg; }

void Piece::setPosition(std::pair<int, int> newPos) { position = newPos; }
