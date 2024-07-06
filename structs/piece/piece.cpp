#include "piece.hpp"
#include <array>
#include <map>
#include <vector>

Piece::Piece()
    : position(std::make_pair(0, 0)),
      pieceGrid(std::array<std::array<bool, 3>, 3>{
          std::array<bool, 3>{false, false, false},
          std::array<bool, 3>{false, false, false},
          std::array<bool, 3>{false, false, false}}) {}

Piece::~Piece() {}

void Piece::rotate(int rotation) { pieceGrid.rotate(rotation); }

void Piece::offset(char c) {
  // map the chars to offsets
  std::map<char, std::pair<int, int>> offsetVals = {
      {'d', {1, 0}}, {'l', {0, -1}}, {'r', {0, 1}}};

  // check if the offset won't put the piece out of bound
  for (std::pair<int, int> coords : getLowerPoints()) {
    if (coords.first + offsetVals[c].first > 23)
      return;
  }

  for (std::pair<int, int> coords : getLeftmostPoints()) {
    if (coords.second + offsetVals[c].second < 0)
      return;
  }

  for (std::pair<int, int> coords : getRightmostPoints()) {
    if (coords.second + offsetVals[c].second >= 10)
      return;
  }

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
      if (pieceGrid.getGrid()[i][j]) {
        pieces.push_back({i + position.first, j + position.second});
      }
    }
  }

  return pieces;
}

std::vector<std::pair<int, int>> Piece::getLowerPoints() {
  std::vector<std::pair<int, int>> lowerPointsCoords;

  for (int i = 2; i >= 0; i--) {
    bool found = false;
    for (int j = 0; j < 3; j++) {
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

std::vector<std::pair<int, int>> Piece::getUpperPoints() {
  std::vector<std::pair<int, int>> upperPointsCoords;

  for (int i = 0; i < 3; i++) {
    bool found = false;
    for (int j = 0; j < 3; j++) {
      if (pieceGrid.getGrid()[i][j]) {
        found = true;
        upperPointsCoords.push_back({i + position.first, j + position.second});
      }
    }

    if (found) {
      break;
    }
  }

  return upperPointsCoords;
}

std::vector<std::pair<int, int>> Piece::getRightmostPoints() {
  std::vector<std::pair<int, int>> rightmostPointsCoords;

  for (int j = 2; j >= 0; j--) {
    bool found = false;
    for (int i = 0; i < 3; i++) {
      if (pieceGrid.getGrid()[i][j]) {
        found = true;
        rightmostPointsCoords.push_back(
            {i + position.first, j + position.second});
      }
    }

    if (found) {
      break;
    }
  }

  return rightmostPointsCoords;
}

std::vector<std::pair<int, int>> Piece::getLeftmostPoints() {
  std::vector<std::pair<int, int>> leftmostPointsCoords;

  for (int j = 0; j < 3; j++) {
    bool found = false;
    for (int i = 0; i < 3; i++) {
      if (pieceGrid.getGrid()[i][j]) {
        found = true;
        leftmostPointsCoords.push_back(
            {i + position.first, j + position.second});
      }
    }

    if (found) {
      break;
    }
  }

  return leftmostPointsCoords;
}

void Piece::setPieceGrid(PieceGrid pg) { pieceGrid = pg; }

void Piece::setPosition(std::pair<int, int> newPos) { position = newPos; }

std::pair<int, int> Piece::getPosition() { return position; }
