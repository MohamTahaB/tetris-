#include "game.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Game::Game()
    : piece(Piece()), board(std::array<std::array<bool, 10>, 24>{}),
      gameOver(false) {}

Game::~Game() { piece.~Piece(); }

void Game::setPiece(PieceGrid pg) {
  piece.setPieceGrid(pg);

  // TODO! add funcs to check the max up, left, right most points to know how to
  // position the reference, which will be now simply <0,0>

  piece.setPosition({0, 0});
}

void Game::resetBoard() {
  for (int i = 0; i < 24; i++) {
    for (int j = 0; j < 10; j++) {
      board[i][j] = false;
    }
  }
}

void Game::clearCompleteLines() {
  // clear any lines that are complete, and compact the result into the bottom
  // of the board
  int offset = 0;
  for (int i = 23; i >= 0; i--) {
    bool clearLine = true;
    for (int j = 0; j < 10; j++) {
      if (!board[i][j]) {
        clearLine = false;
        break;
      }
    }

    // check if the line should not be cleared, then offset it
    if (!clearLine) {
      for (int j = 0; j < 10; j++) {
        board[i + offset][j] = board[i][j];
      }
    }

    else {
      for (int j = 0; j < 10; j++) {
        board[i][j] = false;
      }
      offset++;
    }
  }
}

bool Game::isPieceSet() {
  bool pieceIsSet = false;
  for (std::pair<int, int> coords : piece.getLowerPoints()) {
    if (coords.first == 23 || board[coords.first + 1][coords.second]) {
      pieceIsSet = true;
      break;
    }
  }

  return pieceIsSet;
}

bool Game::isPieceValid() {

  // upper bound
  for (std::pair<int, int> coords : piece.getUpperPoints()) {
    if (coords.first < 0 || coords.first > 23 || coords.second < 0 ||
        coords.second > 9) {
      // out of bounds
      return false;
    }
    if (board[coords.first][coords.second]) {
      // place does not fit
      return false;
    }
  }

  // lower bound
  for (std::pair<int, int> coords : piece.getLowerPoints()) {
    if (coords.first < 0 || coords.first > 23 || coords.second < 0 ||
        coords.second > 9) {
      // out of bounds
      return false;
    }
    if (board[coords.first][coords.second]) {
      // place does not fit
      return false;
    }
  }

  // right most points
  for (std::pair<int, int> coords : piece.getRightmostPoints()) {
    if (coords.first < 0 || coords.first > 23 || coords.second < 0 ||
        coords.second > 9) {
      // out of bounds
      return false;
    }
    if (board[coords.first][coords.second]) {
      // place does not fit
      return false;
    }
  }

  // leftmost points
  for (std::pair<int, int> coords : piece.getLeftmostPoints()) {
    if (coords.first < 0 || coords.first > 23 || coords.second < 0 ||
        coords.second > 9) {
      // out of bounds
      return false;
    }
    if (board[coords.first][coords.second]) {
      // place does not fit
      return false;
    }
  }

  // the piece does fit and is not out of bounds
  return true;
}

void Game::movePiece(char c) {

  // offset the piece first
  piece.offset(c);

  // if the move is not valid: revert
  if (!isPieceValid()) {
    switch (c) {
    case 'd':
      piece.offset('u');
      break;

    case 'l':
      piece.offset('r');
      break;

    case 'r':
      piece.offset('l');
      break;
    }
  }
}

void Game::rotatePiece(int r) {

  // following the same logic as in movePiece: rotate the piece first
  piece.rotate(r);

  // if the move is not valid, revert
  if (!isPieceValid()) {
    piece.rotate(4 - r);
  }
}

void Game::pieceCycle(char c, int r) {

  // regroups the movements of pieces and the logic of the game.
  // first off, nothing is done before checking whether the completed lines were
  // cleaned
  clearCompleteLines();

  // move then rotate
  movePiece(c);
  rotatePiece(r);

  // check if the piece is set
  if (isPieceSet()) {
    for (std::pair<int, int> coords : piece.getCases()) {
      board[coords.first][coords.second] = true;
    }

    Piece p;
    piece = p;

    // check whether moving is possible
    for (std::pair<int, int> coords : piece.getCases()) {
      if (board[coords.first][coords.second]) {
        gameOver = true;
        break;
      }
    }
  }
}

std::array<std::array<bool, 10>, 24> Game::getBoard() { return board; }

Piece Game::getPiece() { return piece; }

bool Game::isGameOver() { return gameOver; }

void Game::debug() {
  char c;
  int r;
  std::array<std::array<char, 10>, 24> charBoard;

  while (std::cin >> c >> r && !isGameOver()) {
    for (int i = 0; i < 24; i++) {
      for (int j = 0; j < 10; j++) {
        charBoard[i][j] = 'O';
      }
    }

    pieceCycle(c, r);
    for (int i = 0; i < 24; i++) {
      for (int j = 0; j < 10; j++) {
        charBoard[i][j] = (getBoard()[i][j] ? '@' : 'O');
      }
    }

    for (std::pair<int, int> coords : piece.getCases()) {
      charBoard[coords.first][coords.second] = '@';
    }

    for (int i = 0; i < 24; i++) {
      for (int j = 0; j < 10; j++) {
        std::cout << charBoard[i][j];
      }
      std::cout << std::endl;
    }
  }
}

void Game::launch() {
  const int pixelSize = 50, screenWidth = 10, screenHeight = 24;

  sf::RenderWindow window(
      sf::VideoMode(screenWidth * pixelSize, screenHeight * pixelSize),
      "Ctris");

  window.setFramerateLimit(60);

  sf::RectangleShape pixels[screenHeight][screenWidth];

  for (int x = 0; x < screenHeight; x++) {
    for (int y = 0; y < screenWidth; y++) {
      pixels[x][y].setSize(sf::Vector2f(pixelSize, pixelSize));
      pixels[x][y].setPosition(y * pixelSize, x * pixelSize);
    }
  }

  char c = 'z';
  int r = 0;

  while (window.isOpen() && !isGameOver()) {
    c = 'z';
    r = 0;

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      // detect key presses
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Down) {
          c = 'd';
        }
        if (event.key.code == sf::Keyboard::Right) {
          c = 'r';
        }
        if (event.key.code == sf::Keyboard::Left) {
          c = 'l';
        }
        if (event.key.code == sf::Keyboard::Space) {
          r = 1;
        }
      }
    }

    pieceCycle(c, r);

    window.clear();

    // clear the pixels, and mark the game board
    for (int x = 0; x < screenHeight; x++) {
      for (int y = 0; y < screenWidth; y++) {
        pixels[x][y].setFillColor((board[x][y]) ? sf::Color::White
                                                : sf::Color::Black);
      }
    }

    // mark the game occupied pixels and the piece pixels
    for (std::pair<int, int> coords : piece.getCases()) {
      pixels[coords.first][coords.second].setFillColor(sf::Color::White);
    }

    // draw pixels
    for (int x = 0; x < screenHeight; x++) {
      for (int y = 0; y < screenWidth; y++) {
        window.draw(pixels[x][y]);
      }
    }

    // display content of the window
    window.display();
  }

  return;
}