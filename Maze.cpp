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

void Maze::parcoursenlargeur(int startingx, int startingy, int endingx, int endingy){
    std::vector<Case> queue;
    queue.push_back(maze[startingx][startingy]);
    while (!queue.empty()){
        Case current = queue.front();
        queue.erase(queue.begin());
        if (current.getSymbol() == 'E'){
            std::cout << "Path found!" << std::endl;
            break;
        }
        else{
            if (maze[current.getSymbol() + 1][current.getSymbol()].getSymbol() != 'X' && maze[current.getSymbol() + 1][current.getSymbol()].getVisited() != true){
                queue.push_back(maze[current.getSymbol() + 1][current.getSymbol()]);
                maze[current.getSymbol() + 1][current.getSymbol()].setVisited();
                parcoursenlargeur(current.getSymbol() + 1, current.getSymbol(), endingx, endingy);
            }
            if (maze[current.getSymbol()][current.getSymbol() + 1].getSymbol() != 'X' && maze[current.getSymbol()][current.getSymbol() + 1].getVisited() != true){
                queue.push_back(maze[current.getSymbol()][current.getSymbol() + 1]);
                maze[current.getSymbol()][current.getSymbol() + 1].setVisited();
                parcoursenlargeur(current.getSymbol(), current.getSymbol() + 1, endingx, endingy);
            }
            if (maze[current.getSymbol() - 1][current.getSymbol()].getSymbol() != 'X' && maze[current.getSymbol() - 1][current.getSymbol()].getVisited() != true){
                queue.push_back(maze[current.getSymbol() - 1][current.getSymbol()]);
                maze[current.getSymbol() - 1][current.getSymbol()].setVisited();
                parcoursenlargeur(current.getSymbol() - 1, current.getSymbol(), endingx, endingy);
            }
            if (maze[current.getSymbol()][current.getSymbol() - 1].getSymbol() != 'X' && maze[current.getSymbol()][current.getSymbol() - 1].getVisited() != true){
                queue.push_back(maze[current.getSymbol()][current.getSymbol() - 1]);
                maze[current.getSymbol()][current.getSymbol() - 1].setVisited();
                parcoursenlargeur(current.getSymbol(), current.getSymbol() - 1, endingx, endingy);
            }
        }
    }
}
