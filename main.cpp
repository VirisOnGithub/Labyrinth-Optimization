#include <SFML/Window.hpp>
#include <iostream>
#include "Case.h"
#include "Maze.h"

int main() {
  sf::Window window(sf::VideoMode(800, 600), "Maze");
  sf::Event event;
  Maze maze(10, 10);
  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape)
          window.close();
        if (event.key.code == sf::Keyboard::Space) {
          maze.breadthFirstSearch(0, 0, 9, 9, 10, 10);
          maze.display();
        }
      }
    }
  }
}

/*int main() {
  int sizex, sizey, startingx, startingy, endingx, endingy, wallx, wally;
  char answer;

  std::cout << "Enter the size of the maze (x y): ";
  std::cin >> sizex >> sizey;
  Maze maze(sizex, sizey);
  std::cout << std::endl;
  maze.display();
  std::cout << std::endl;

  do {
    std::cout << "Enter starting position (x y): ";
    std::cin >> startingx >> startingy;
  } while (startingx < 1 || startingx > sizex || startingy < 1 ||
           startingy > sizey);
  maze[startingx - 1][startingy - 1].setStartCase();
  std::cout << std::endl;
  maze.display();
  std::cout << std::endl;

  do {
    std::cout << "Enter ending position (x y): ";
    std::cin >> endingx >> endingy;
  } while ((endingx == startingx && endingy == startingy) || endingx < 1 ||
           endingx > sizex || endingy < 1 || endingy > sizey);
  maze[endingx - 1][endingy - 1].setEndCase();
  std::cout << std::endl;
  maze.display();
  std::cout << std::endl;

  std::cout << "Do you want to add a wall? (y/n) ";
  std::cin >> answer;
  while (answer == 'y') {
    std::cout << "Enter wall position (x y): ";
    do {
      std::cin >> wallx >> wally;
    } while ((wallx == startingx && wally == startingy) ||
             (wallx == endingx && wally == endingy) || wallx < 1 ||
             wallx > sizex || wally < 1 || wally > sizey);
    maze[wallx - 1][wally - 1].setWall();
    std::cout << std::endl;
    maze.display();
    std::cout << std::endl;
    std::cout << "Do you want to add another wall? (y/n) ";
    std::cin >> answer;
  }
  maze.display();
  std::cout << std::endl;

  short int choice;

  std::cout << "1) Breadth-first search" << std::endl;
  std::cout << "2) Depth-first search" << std::endl;
  std::cout << "Enter your choice: ";
  std::cin >> choice;
  while (choice != 1 && choice != 2) {
    std::cout << "Invalid choice. Please enter 1 or 2: ";
    std::cin >> choice;
  }
  std::cout << std::endl;
  switch (choice) {
    case 1:
      maze.breadthFirstSearch(startingx - 1, startingy - 1, endingx - 1,
                              endingy - 1, sizex, sizey);
      break;

    case 2:
      maze.depthFirstSearch(startingx - 1, startingy - 1, endingx - 1,
                            endingy - 1, sizex, sizey);
      break;

    default:
      break;
  }
}*/