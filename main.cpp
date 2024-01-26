#include <iostream>
#include "Case.h"
#include "Maze.h"

int main()
{
    int sizex, sizey, startingx, startingy, endingx, endingy;
    std::cout << "Enter the size of the maze (x y): ";
    std::cin >> sizex >> sizey;

    std::cout << "Enter starting position (x y): ";
    std::cin >> startingx >> startingy;

    std::cout << "Enter ending position (x y): ";
    std::cin >> endingx >> endingy;

    Maze maze(sizex, sizey);
    maze[startingy - 1][startingx - 1] = 'S';
    maze[endingy - 1][endingx - 1] = 'E';
    
    maze.display();

    return 0;
}