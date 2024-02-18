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
Maze maze(100, 100);

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Maze");
  sf::Text text;
  std::string inputx, inputy, errorMessage;
  int x, y, xstart=0, ystart=0, xend=0, yend=0, cpt=0;
  bool menu = true, first=true, hasStart=false, hasEnd=false, displayCpt=false;

  // Icone
  loadIcon(window);


  // Font
  loadFont(font);

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
        try {
          int sizex = std::stoi(bufsizex);
          int sizey = std::stoi(bufsizey);

          if (sizex <= 0 || sizey <= 0) {
            errorMessage = "Erreur : La largeur et la hauteur du labyrinthe doivent être supérieures à 0.";
          } else {
            inputx = bufsizex;
            inputy = bufsizey;
            menu = false;
            errorMessage = ""; // Réinitialise le message d'erreur
          }
        } catch (std::invalid_argument& e) {
          errorMessage = "Erreur : La largeur et la hauteur du labyrinthe doivent être des nombres entiers.";
        }
      }

      if (!errorMessage.empty()) {
        ImGui::Text("%s", errorMessage.c_str());
      }
      ImGui::End();
      window.clear();
    } else {
      if (first) {
        x = std::stoi(inputx);
        y = std::stoi(inputy);
        maze.resize(x, y);
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
      ImGui::RadioButton("A*", &choiceSearch, 2);

      float buttonWidth = ImGui::CalcTextSize("Reset").x;
      float windowWidth = ImGui::GetWindowSize().x;
      float centerPosX = (windowWidth - buttonWidth) / 2.0f;
      ImGui::SetCursorPosX(centerPosX);
      if (ImGui::Button("Reset")) {
        std::cout << "Reset" << std::endl;
        displayCpt = false;
        cpt = 0;
        maze.reset();
        hasStart = false;
        hasEnd = false;
        first = true;
      }
      ImGui::End();

      ImGui::Begin("Start Button", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
      ImGui::SetWindowFontScale(1);
      ImGui::SetWindowSize(ImVec2(200, 50));
      ImGui::SetWindowPos(ImVec2(550, 550));
      ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - ImGui::CalcTextSize("Start").x / 2);
      if (ImGui::Button("Start")) {
        std::cout << "Start..." << std::endl;
        maze.partialReset();
        cpt=0;
        displayCpt=false;
        switch (choiceSearch) {
          case 0:
            maze.breadthFirstSearch(xstart, ystart, xend, yend, x, y, cpt, window);
            break;
          case 1:
            maze.depthFirstSearch(xstart, ystart, xend, yend, x, y, cpt, window);
            break;
          case 2:
            maze.aStar(xstart, ystart, xend, yend, x, y, cpt, window);
            break;
          default:
            break;
        }
        displayCpt = true;
      }
      ImGui::End();

      if (displayCpt) {
        ImGui::Begin("Cpt", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        ImGui::SetWindowFontScale(1);
        ImGui::SetWindowSize(ImVec2(200, 50));
        ImGui::SetWindowPos(ImVec2(550, 500));
        ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - ImGui::CalcTextSize("Cases parcourues: 00").x / 2);
        ImGui::Text("Cases parcourues: %d", cpt);
        ImGui::End();
      }


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
                  if (!hasStart && maze[i][j].getColor() != sf::Color::Black) {
                    hasStart = true;
                    maze[i][j].setStartCase();
                    xstart = i;
                    ystart = j;
                  }
                  break;
                case 1:
                  if (!hasEnd && maze[i][j].getColor() != sf::Color::Black) {
                    hasEnd = true;
                    maze[i][j].setEndCase();
                    xend = i;
                    yend = j;
                  }
                  break;
                case 2:
                  if(maze[i][j].getColor() != sf::Color::Green && maze[i][j].getColor() != sf::Color::Red){
                    maze[i][j].setColor(sf::Color::Black);
                    maze[i][j].setWall();
                  }
                  break;
                default:
                  break;
              }
            }
          }

          Rect.setFillColor(maze[i][j].getColor());


          window.draw(Rect);
        }
      }

    }
    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();
}