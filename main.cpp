#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include "Maze.h"
#include "functions.h"
#include "imgui-master/imgui.h"
#include "imgui-sfml/imgui-SFML.h"

sf::Font font;

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Maze");
  sf::Text text;
  std::string inputx, inputy;
  int x, y;
  bool menu = true, first=true;
  std::vector<std::vector<sf::Color>> colors;

  // Icone
  sf::Image icon;
  if (!icon.loadFromFile("assets/icon.jpg")) {
    std::cerr << "Failed to load icon\n";
  } else {
    std::cout << "Icon loaded successfully\n";
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
  }

  // Font
  if (!font.loadFromFile("fonts/arial.ttf")) {
    std::cerr << "Failed to load font\n";
  } else {
    std::cout << "Font loaded successfully\n";
  }
  window.setFramerateLimit(60);
  if (!ImGui::SFML::Init(window)) {
    return -1;
  }

  char bufsizex[10], bufsizey[10];
  memset(bufsizex, 0, sizeof(bufsizex));
  memset(bufsizey, 0, sizeof(bufsizey));

  sf::Clock deltaClock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(window, event);

      if (event.type == sf::Event::Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
      }
    }

    ImGui::SFML::Update(window, deltaClock.restart());

    if (menu) {
      ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
      ImGui::SetWindowFontScale(3);
      ImGui::SetWindowPos(ImVec2(100, 50));
      ImGui::SetWindowSize(ImVec2(600, 60));

      // Calculer la position horizontale pour centrer le texte
      float textWidth = ImGui::CalcTextSize("Make your maze").x;
      float windowWidth = ImGui::GetWindowSize().x;
      float centerPosX = (windowWidth - textWidth) / 2.0f;

      ImGui::SetCursorPosX(centerPosX);

      ImGui::Text("Make your maze");
      ImGui::End();


      ImGui::Begin("##", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
      ImGui::SetWindowFontScale(1);

      ImGui::SetWindowSize(ImVec2(600, 400));
      ImGui::SetWindowPos(ImVec2(100, 100));
      ImGui::Text("Largeur du labyrinthe");
      ImGui::InputText("largeur", bufsizex, sizeof(bufsizex));
      ImGui::Text("Hauteur du labyrinthe");
      ImGui::InputText("hauteur", bufsizey, sizeof(bufsizey));
      float buttonWidth = ImGui::CalcTextSize("Reset").x;
      ImGui::SetCursorPosX((windowWidth - buttonWidth) / 2.0f);
      if (ImGui::Button("OK")) {
        inputx = bufsizex;
        inputy = bufsizey;
        menu = false;
      }
      ImGui::End();
      window.clear();
    } else {
      if (first) {
        x = std::stoi(inputx);
        y = std::stoi(inputy);
        Maze maze(x, y);
        colors.resize(x, std::vector<sf::Color>(y, sf::Color::White));
        first = false;
      }

      // Titre
      ImGui::Begin("Maze", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
      ImGui::SetWindowFontScale(1);
      ImGui::SetWindowSize(ImVec2(600, 50));
      ImGui::SetWindowPos(ImVec2(100, 50));
      ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - ImGui::CalcTextSize("Maze size: 00").x / 2);
      ImGui::Text("Maze size: %sx%s", inputx.c_str(), inputy.c_str());
      ImGui::End();

      //inputs 
      static int choiceCase, choiceSearch;

      ImGui::Begin("Options", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
      ImGui::SetWindowFontScale(1);
      ImGui::SetWindowSize(ImVec2(200, 400));
      ImGui::SetWindowPos(ImVec2(550, 150));

      ImGui::Text("Cases");
      ImGui::RadioButton("Start", &choiceCase, 0);
      ImGui::RadioButton("End", &choiceCase, 1);
      ImGui::RadioButton("Wall", &choiceCase, 2);
      
      ImGui::Text("Search");
      ImGui::RadioButton("Breadth-first", &choiceSearch, 0);
      ImGui::RadioButton("Depth-first", &choiceSearch, 1);

      float buttonWidth = ImGui::CalcTextSize("Reset").x;
      float windowWidth = ImGui::GetWindowSize().x;
      float centerPosX = (windowWidth - buttonWidth) / 2.0f;
      ImGui::SetCursorPosX(centerPosX);
      if (ImGui::Button("Reset")) {
        menu = true;
        first = true;
      }
      ImGui::End();

      int caseHeight = std::min(600 / x, 400 / y);
      window.clear();

      for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
          sf::RectangleShape Rect(sf::Vector2f(caseHeight, caseHeight));
          Rect.setPosition(i * caseHeight+(window.getSize().x-200 - x*caseHeight)/2.0, j * caseHeight+(window.getSize().y+100 - y*caseHeight)/2.0);
          Rect.setFillColor(sf::Color::White);
          Rect.setOutlineThickness(1);
          Rect.setOutlineColor(sf::Color::Black);

          // Vérifier si le bouton de la souris est pressé et si la position de la souris est à l'intérieur de la case
          if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (Rect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
              switch (choiceCase) {
                case 0:
                  colors[i][j] = sf::Color::Green;
                  break;
                case 1:
                  colors[i][j] = sf::Color::Red;
                  break;
                case 2:
                  colors[i][j] = sf::Color::Black;
                  break;
                default:
                  break;
              }
            }
          }

          Rect.setFillColor(colors[i][j]);


          window.draw(Rect);
        }
      }

    }
    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();
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