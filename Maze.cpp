#include "Maze.h"

Maze::Maze(int sizex, int sizey) {
  maze.resize(sizex, std::vector<Case>(sizey));
}

Maze::~Maze() {}

void Maze::display() const {
  for (unsigned int i = 0; i < maze.size(); i++) {
    for (unsigned int j = 0; j < maze[i].size(); j++) {
      std::cout << maze[i][j].getSymbol();
    }
    std::cout << std::endl;
  }
}

std::vector<Case>& Maze::operator[](int index) {
  return maze[index];
}
