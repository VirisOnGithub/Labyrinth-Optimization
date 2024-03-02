#include "Maze.h"
#include "Case.h"
#include <iostream>
#include <queue>
#include <stack>
#include <cmath>
#include <algorithm>

Maze::Maze(int sizex, int sizey)
{
  maze.resize(sizex, std::vector<Case>(sizey));
}

Maze::~Maze() {}

void Maze::display() const
{
  system("clear");
  for (unsigned int i = 0; i < maze.size(); i++)
  {
    for (unsigned int j = 0; j < maze[i].size(); j++)
    {
      std::cout << maze[i][j].getSymbol();
    }
    std::cout << std::endl;
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
                              int sizey)
{
  std::queue<std::pair<int, int>> q;
  std::vector<std::vector<bool>> visited(sizex,
                                         std::vector<bool>(sizey, false));
  int cellCount = 0; // Counter for the number of cells visited

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
  cellCount++;

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
      std::cout << "Nombre de cases parcourues : " << cellCount << std::endl;
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
        cellCount++;
      }
    }
  }

  std::cout << "Aucun chemin trouvé jusqu'à la destination." << std::endl;
  std::cout << "Nombre de cases parcourues : " << cellCount << std::endl;
}

void Maze::depthFirstSearch(int startingx,
                            int startingy,
                            int endingx,
                            int endingy,
                            int sizex,
                            int sizey)
{
  std::stack<std::pair<int, int>> s;
  std::vector<std::vector<bool>> visited(sizex,
                                         std::vector<bool>(sizey, false));
  int cellCount = 0; // Counter for the number of cells visited

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
  cellCount++;

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
      std::cout << "Nombre de cases parcourues : " << cellCount << std::endl;
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
        cellCount++;
      }
    }
  }

  std::cout << "Aucun chemin trouvé jusqu'à la destination." << std::endl;
  std::cout << "Nombre de cases parcourues : " << cellCount << std::endl;
}

void Maze::drawPath(int endingx, int endingy)
{
  Case *current = &maze[endingx][endingy];
  current = current->parent;
  while (current->parent != nullptr)
  {
    current->setSymbol('*');
    current = current->parent;
  }

  display();
}

void Maze::aStar(int startingx,
                 int startingy,
                 int endingx,
                 int endingy,
                 int sizex,
                 int sizey)
{
  std::vector<std::pair<float, std::pair<int, int>>> v; // (distance, (x, y))
  std::vector<std::vector<bool>> visited(sizex,
                                         std::vector<bool>(sizey, false));

  std::cout << "Starting A*..." << std::endl;
  int cellcount = 0;

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
  cellcount++;

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
      std::cout << "Nombre de cases parcourues : " << cellcount << std::endl;
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
        cellcount++;
      }
    }
  }

  std::cout << "Aucun chemin trouvé jusqu'à la destination." << std::endl;
  std::cout << "Nombre de cases parcourues : " << cellcount << std::endl;
}

void Maze::setwallrandom(int startingx,
                         int startingy,
                         int endingx,
                         int endingy,
                         int sizex,
                         int sizey)
{
  int wallx, wally;
  wallx = rand() % sizex;
  wally = rand() % sizey;
  if (!(maze[wallx][wally].getEndCase()) && !(maze[wallx][wally].getStartCase()) && !(maze[wallx][wally].getWall()))
  {
    maze[wallx][wally].setWall();
    std::cout << "Wall added at position (" << wallx + 1 << ", " << wally + 1 << ")." << std::endl;
    std::cout << std::endl;
  }
  else
  {
    std::cout << "Error: Wall case must be elsewhere than the start, end or wall case." << std::endl;
    std::cout << "Wall not added at position (" << wallx + 1 << ", " << wally + 1 << ")." << std::endl;
    setwallrandom(startingx, startingy, endingx, endingy, sizex, sizey);
  }
}

void Maze::setwallnotrandom(int startingx,
                            int startingy,
                            int endingx,
                            int endingy,
                            int sizex,
                            int sizey)
{
  int wallx, wally;
  std::cout << "Enter wall position (x y): ";
  do
  {
    std::cin >> wallx >> wally;
  } while ((wallx == startingx && wally == startingy) ||
           (wallx == endingx && wally == endingy) || wallx < 1 ||
           wallx > sizex || wally < 1 || wally > sizey);
  maze[wallx - 1][wally - 1].setWall();
}

float Maze::distance(int x, int y, int endingx, int endingy)
{
  return sqrt(pow(endingx - x, 2) + pow(endingy - y, 2));
}