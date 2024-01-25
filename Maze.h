#ifndef MAZE_H
#define MAZE_H

#include "Case.h"
#include <vector>
#include <iostream>

class Maze
{
private:
    std::vector<std::vector<Case>> maze;

public:
    Maze(int sizex, int sizey);
    ~Maze();
    void display() const;
};

#endif // MAZE_H
