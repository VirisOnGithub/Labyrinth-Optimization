#include <cstdlib>
#include <ctime>
#include <iostream>
#include <time.h>
#include "Maze.h"

int main()
{
  clock_t start, end;
  int sizex, sizey, startingx, startingy, endingx, endingy;
  char answer1, answer2;
  bool reset = true;

  std::cout << "Bienvenue dans le Projet d'Optimisation de Labyrinthe !" << std::endl;
  std::cout << "-------------------------------------------------------" << std::endl;
  std::cout << "Ce programme vous permet de créer et de résoudre des labyrinthes." << std::endl;
  std::cout << std::endl;
  std::cout << "Appuyez sur n'importe quelle touche pour continuer..." << std::endl;
  std::cin.ignore();
  system("clear");

  std::cout << "Enter the size of the maze (x y): ";
  std::cin >> sizex >> sizey;
  Maze maze(sizex, sizey);
  Maze maze1(sizex, sizey);
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

  while (reset)
  {
    maze1 = maze;
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
      start = clock();
      maze1.breadthFirstSearch(startingx - 1, startingy - 1, endingx - 1,
                               endingy - 1, sizex, sizey);
      end = clock();
      break;

    case 2:
      start = clock();
      maze1.depthFirstSearch(startingx - 1, startingy - 1, endingx - 1,
                             endingy - 1, sizex, sizey);
      end = clock();
      break;

    case 3:
      start = clock();
      maze1.aStar(startingx - 1, startingy - 1, endingx - 1, endingy - 1,
                  sizex, sizey);
      end = clock();
      break;

    default:
      break;
    }
    std::cout << std::endl;
    std::cout << "Temps écoulé : " << (double)(end - start) / CLOCKS_PER_SEC
              << " secondes" << std::endl;

    std::cout << "Voulez vous changer de parcours ? (y/n)" << std::endl;
    char choix;
    std::cin >> choix;
    if (choix == 'y')
    {
      reset = true;
    }
    else
    {
      reset = false;
    }
    std::cout << std::endl;
  }
}