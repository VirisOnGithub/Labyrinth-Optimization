#include <iostream>
#include "Case.h"
#include "Maze.h"

int main()
{
  int sizex, sizey, startingx, startingy, endingx, endingy;
  char answer1, answer2;

  std::cout << "Enter the size of the maze (x y): ";
  std::cin >> sizex >> sizey;
  Maze maze(sizex, sizey);
  std::cout << std::endl;
  maze.display();
  std::cout << std::endl;

  do
  {
    std::cout << "Enter starting position (x y): ";
    std::cin >> startingx >> startingy;
  } while (startingx < 1 || startingx > sizex || startingy < 1 ||
           startingy > sizey);
  maze[startingx - 1][startingy - 1].setStartCase();
  std::cout << std::endl;
  maze.display();
  std::cout << std::endl;

  do
  {
    std::cout << "Enter ending position (x y): ";
    std::cin >> endingx >> endingy;
  } while ((endingx == startingx && endingy == startingy) || endingx < 1 ||
           endingx > sizex || endingy < 1 || endingy > sizey);
  maze[endingx - 1][endingy - 1].setEndCase();
  std::cout << std::endl;
  maze.display();
  std::cout << std::endl;

  std::cout << "Do you want to add a wall? (y/n) ";
  std::cin >> answer1;
  while (answer1 == 'y')
  {
    std::cout << "Randomly add a wall? (y/n) ";
    std::cin >> answer2;
    if (answer2 == 'n')
    {
      maze.setwallnotrandom(startingx, startingy, endingx, endingy, sizex,
                            sizey);
    }
    else
    {
      maze.setwallrandom(startingx, startingy, endingx, endingy, sizex, sizey);
    }

    std::cout << std::endl;
    maze.display();
    std::cout << std::endl;
    std::cout << "Do you want to add another wall? (y/n) ";
    std::cin >> answer1;
  }
  maze.display();
  std::cout << std::endl;

  short int choice;

  std::cout << "1) Breadth-first search" << std::endl;
  std::cout << "2) Depth-first search" << std::endl;
  std::cout << "3) A* search" << std::endl;
  std::cout << "Enter your choice: ";
  std::cin >> choice;
  while (choice != 1 && choice != 2 && choice != 3)
  {
    std::cout << "Invalid choice. Please enter 1, 2 or 3 : ";
    std::cin >> choice;
  }
  std::cout << std::endl;
  switch (choice)
  {
  case 1:
    maze.breadthFirstSearch(startingx - 1, startingy - 1, endingx - 1,
                            endingy - 1, sizex, sizey);
    break;

  case 2:
    maze.depthFirstSearch(startingx - 1, startingy - 1, endingx - 1,
                          endingy - 1, sizex, sizey);
    break;

  case 3:
    maze.aStarSearch(startingx - 1, startingy - 1, endingx - 1, endingy - 1,
                     sizex, sizey);
    break;

  default:
    break;
  }
}