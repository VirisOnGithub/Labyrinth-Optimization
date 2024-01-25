#include <iostream>
#include "Case.h"
#include "Maze.h"

int main()
{
    int sizex, sizey, startingx, startingy;
    std::cout << "Enter the size of the maze (x y): ";
    std::cin >> sizex >> sizey;

    std::cout << "Enter starting position (x y): ";
    std::cin >> startingx >> startingy;

    Maze maze(sizex, sizey);
    maze[startingy - 1][startingx - 1] = 'S';

    maze.display();

    return 0;
}