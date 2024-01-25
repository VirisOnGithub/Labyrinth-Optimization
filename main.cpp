#include <iostream>
#include "Case.h"
#include "Maze.h"

int main()
{
    int sizex, sizey;
    std::cout << "Enter the size of the maze (x y): ";
    std::cin >> sizex >> sizey;

    Maze maze(sizex, sizey);

    maze.display();

    return 0;
}