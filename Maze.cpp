#include "Maze.h"
#include "Case.h"
#include <iostream>
#include <queue>
#include <stack>
#include <cmath>

Maze::Maze(int sizex, int sizey)
{
  maze.resize(sizex, std::vector<Case>(sizey));
}

Maze::~Maze() {}

void Maze::display() const
{
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

void Maze::aStarSearch(int startingx,
                       int startingy,
                       int endingx,
                       int endingy,
                       int sizex,
                       int sizey)
{
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      q;
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
    int x = q.top().first;
    int y = q.top().second;
    q.pop();
    maze[x][y].setDistance(sqrt(pow(endingx - x, 2) + pow(endingy - y, 2)));

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
    std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (const auto &dir : directions)
    {
      int nx = x + dir.first;
      int ny = y + dir.second;

      // Vérifier si les coordonnées du voisin sont valides
      if (nx >= 0 && nx < sizex && ny >= 0 && ny < sizey)
      {
        maze[nx][ny].setDistance(sqrt(pow(endingx - nx, 2) + pow(endingy - ny, 2)));

        // Vérifier si le voisin n'a pas été visité et n'est pas un mur
        if (!visited[nx][ny] && !maze[nx][ny].getVisited() && !maze[nx][ny].getWall())
        {
          if (maze[nx][ny].getDistance() < maze[x][y].getDistance())
          {
            maze[nx][ny].parent = &maze[x][y];
            q.push(std::make_pair(nx, ny));
            visited[nx][ny] = true;
            cellCount++;
          }
          else if (maze[nx][ny].getDistance() > maze[x][y].getDistance() + 1)
          {
            maze[nx][ny].setDistance(maze[x][y].getDistance() + 1);
          }
          else
          {
            maze[nx][ny].setDistance(maze[x][y].getDistance());
          }
        }
      }
    }
  }

  std::cout << "Aucun chemin trouvé jusqu'à la destination." << std::endl;
  std::cout << "Nombre de cases parcourues : " << cellCount << std::endl;
}

void Maze::setwallrandom(int startingx,
                         int startingy,
                         int endingx,
                         int endingy,
                         int sizex,
                         int sizey)
{
  int wallx, wally;
  srand(time(NULL));
  wallx = rand() % sizex;
  wally = rand() % sizey;
  if ((wallx != startingx && wally != startingy) || (wallx != endingx && wally != endingy) || !maze[wallx][wally].getWall())
  {
    maze[wallx][wally].setWall();
  }
  else
  {
    setwallrandom(startingx, startingy, endingx, endingy, sizex, sizey);
  }
}