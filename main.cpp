#include <iostream>
#include "Case.h"

int main()
{
    int sizex, sizey;
    std::cout << "Enter the size of the maze (x y): ";
    std::cin >> sizex >> sizey;
    Case **maze = new Case *[sizex];
    for (int i = 0; i < sizex; i++)
    {
        maze[i] = new Case[sizey];
    }
    for (int i = 0; i < sizex; i++)
    {
        for (int j = 0; j < sizey; j++)
        {
            std::cout << maze[i][j].getSymbol() << " ";
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < sizex; i++)
    {
        delete[] maze[i];
    }
    delete[] maze;
    return 0;
}