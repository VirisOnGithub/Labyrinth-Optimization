#include "Maze.h"

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <cmath>
#include "functions.h"

#include <SFML/Graphics.hpp>
#include <utility>

Maze::Maze(int sizex, int sizey)
{
  maze.resize(sizex, std::vector<Case>(sizey));
}

Maze::~Maze() {}

void Maze::resize(int sizex, int sizey)
{
  maze.resize(sizex, std::vector<Case>(sizey));
}

void Maze::reset()
{
  for (auto &row : maze)
  {
    for (auto &cell : row)
    {
      cell.reset();
    }
  }
}

std::vector<Case> &Maze::operator[](int index)
{
  return maze[index];
}

void Maze::breadthFirstSearch(int startingx,
                              int startingy,
                              int endingx,
                              int endingy,
                              int sizex,
                              int sizey,
                              int &cpt,
                              sf::RenderWindow &window)
{
  std::queue<std::pair<int, int>> q;
  std::vector<std::vector<bool>> visited(sizex,
                                         std::vector<bool>(sizey, false));

  std::cout << "Starting BFS..." << std::endl;

  // Vérifier si les coordonnées de départ et d'arrivée sont valides
  if (startingx < 0 || startingx >= sizex || startingy < 0 ||
      startingy >= sizey || endingx < 0 || endingx >= sizex || endingy < 0 ||
      endingy >= sizey)
  {
    std::cout << "Coordonnées de départ ou d'arrivée invalides." << std::endl;
    return;
  }

  // Ajouter les coordonnées de départ à la file d'attente et marquer comme
  // visité
  q.push(std::make_pair(startingx, startingy));
  visited[startingx][startingy] = true;

  while (!q.empty())
  {
    // Obtenir les coordonnées du prochain nœud à visiter
    int x = q.front().first;
    int y = q.front().second;
    q.pop();

    // Vérifier si on a atteint la destination
    if (x == endingx && y == endingy)
    {
      std::cout << "Destination atteinte !" << std::endl;
      drawPath(endingx, endingy);
      return;
    }

    // Parcourir les voisins du nœud actuel
    // (ici, vous devrez im plémenter votre propre logique pour déterminer les
    // voisins) Exemple : parcours des 4 directions (haut, bas, gauche, droite)
    std::vector<std::pair<int, int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (const auto &dir : directions)
    {
      int nx = x + dir.first;
      int ny = y + dir.second;

      // Vérifier si les coordonnées du voisin sont valides et non visitées
      if (nx >= 0 && nx < sizex && ny >= 0 && ny < sizey && !visited[nx][ny] &&
          !maze[nx][ny].getVisited() && !maze[nx][ny].getWall())
      {
        // Ajouter les coordonnées du voisin à la file d'attente et marquer
        // comme visité
        maze[nx][ny].parent = &maze[x][y];
        q.push(std::make_pair(nx, ny));
        visited[nx][ny] = true;
        cpt++;
      }
    }
  }

  didNotFindPath(window);
}

void Maze::depthFirstSearch(int startingx,
                            int startingy,
                            int endingx,
                            int endingy,
                            int sizex,
                            int sizey,
                            int &cpt,
                            sf::RenderWindow &window)
{
  std::stack<std::pair<int, int>> s;
  std::vector<std::vector<bool>> visited(sizex,
                                         std::vector<bool>(sizey, false));

  std::cout << "Starting DFS..." << std::endl;

  // Vérifier si les coordonnées de départ et d'arrivée sont valides
  if (startingx < 0 || startingx >= sizex || startingy < 0 ||
      startingy >= sizey || endingx < 0 || endingx >= sizex || endingy < 0 ||
      endingy >= sizey)
  {
    std::cout << "Coordonnées de départ ou d'arrivée invalides." << std::endl;
    return;
  }

  // Ajouter les coordonnées de départ à la pile et marquer comme visité
  s.push(std::make_pair(startingx, startingy));
  visited[startingx][startingy] = true;

  while (!s.empty())
  {
    // Obtenir les coordonnées du prochain nœud à visiter
    int x = s.top().first;
    int y = s.top().second;
    s.pop();

    // Vérifier si on a atteint la destination
    if (x == endingx && y == endingy)
    {
      std::cout << "Destination atteinte !" << std::endl;
      drawPath(endingx, endingy);
      return;
    }

    // Parcourir les voisins du nœud actuel
    // (ici, vous devrez im plémenter votre propre logique pour déterminer les
    // voisins) Exemple : parcours des 4 directions (haut, bas, gauche, droite)
    std::vector<std::pair<int, int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (const auto &dir : directions)
    {
      int nx = x + dir.first;
      int ny = y + dir.second;

      // Vérifier si les coordonnées du voisin sont valides et non visitées
      if (nx >= 0 && nx < sizex && ny >= 0 && ny < sizey && !visited[nx][ny] &&
          !maze[nx][ny].getVisited() && !maze[nx][ny].getWall())
      {
        // Ajouter les coordonnées du voisin à la pile et marquer comme visité
        maze[nx][ny].parent = &maze[x][y];
        s.push(std::make_pair(nx, ny));
        visited[nx][ny] = true;
        cpt++;
      }
    }
  }

  didNotFindPath(window);
}

void Maze::aStar(int startingx,
                 int startingy,
                 int endingx,
                 int endingy,
                 int sizex,
                 int sizey,
                 int &cpt,
                 sf::RenderWindow &window)
{
  std::vector<std::pair<float, std::pair<int, int>>> v; // (distance, (x, y))
  std::vector<std::vector<bool>> visited(sizex,
                                         std::vector<bool>(sizey, false));

  std::cout << "Starting A*..." << std::endl;

  // Vérifier si les coordonnées de départ et d'arrivée sont valides
  if (startingx < 0 || startingx >= sizex || startingy < 0 ||
      startingy >= sizey || endingx < 0 || endingx >= sizex || endingy < 0 ||
      endingy >= sizey)
  {
    std::cout << "Coordonnées de départ ou d'arrivée invalides." << std::endl;
    return;
  }

  // Ajouter les coordonnées de départ à la liste et marquer comme visité
  v.push_back(std::make_pair(distance(startingx, startingy, endingx, endingy), std::make_pair(startingx, startingy)));
  visited[startingx][startingy] = true;
  cpt++;

  while (!v.empty())
  {
    // Trier la liste en fonction de la distance
    std::sort(v.begin(), v.end(), [](const std::pair<float, std::pair<int, int>> &a, const std::pair<float, std::pair<int, int>> &b)
              { return a.first > b.first; });

    // Obtenir les coordonnées du prochain nœud à visiter
    int x = v.back().second.first;
    int y = v.back().second.second;
    v.pop_back();

    // Vérifier si on a atteint la destination
    if (x == endingx && y == endingy)
    {
      std::cout << "Destination atteinte !" << std::endl;
      drawPath(endingx, endingy);
      return;
    }

    // Parcourir les voisins du nœud actuel
    // (ici, vous devrez im plémenter votre propre logique pour déterminer les
    // voisins) Exemple : parcours des 4 directions (haut, bas, gauche, droite)
    std::vector<std::pair<int, int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (const auto &dir : directions)
    {
      int nx = x + dir.first;
      int ny = y + dir.second;

      // Vérifier si les coordonnées du voisin sont valides et non visitées
      if (nx >= 0 && nx < sizex && ny >= 0 && ny < sizey && !visited[nx][ny] &&
          !maze[nx][ny].getVisited() && !maze[nx][ny].getWall())
      {
        // Ajouter les coordonnées du voisin à la liste et marquer comme visité
        maze[nx][ny].parent = &maze[x][y];
        v.push_back(std::make_pair(distance(nx, ny, endingx, endingy), std::make_pair(nx, ny)));
        visited[nx][ny] = true;
        cpt++;
      }
    }
  }

  didNotFindPath(window);
}

float Maze::distance(int x1, int y1, int x2, int y2)
{
  return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

void Maze::drawPath(int endingx, int endingy)
{
  Case *current = &maze[endingx][endingy];
  current = current->parent;
  while (current->parent != nullptr)
  {
    current->setColor(sf::Color::Cyan);
    current = current->parent;
  }
}

void Maze::partialReset()
{
  for (auto &row : maze)
  {
    for (auto &cell : row)
    {
      cell.partialReset();
    }
  }
}