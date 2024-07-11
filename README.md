# Ctris

This project is a first take to Tetris in C++, with a SFML GUI.

## Installation

The installation is pretty straightforward.
First off, you need to install [SFML](https://www.sfml-dev.org/download.php), then, basic CMake manipulation from the project root directory:

```
mkdir build && cd build
cmake ../
cmake --build .

```

To run tests, you need to build, then, from the `build` directory, run the tests executable, or `ctest`.

## Instructions

- Arrows to move (right, down, left);
- Space to rotate ninety degrees clockwise.

## Remarks or Contribution

As previously mentionned, this project is a **first take**: it has been done somewhat hastingly, and thus, there are probably many points to reiterate upon or change completely. You are welcome to suggest your remarks and contribute.
