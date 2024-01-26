#include "Maze.h"

#include <iostream>
#include <queue>

Maze::Maze(int sizex, int sizey) {
  maze.resize(sizex, std::vector<Case>(sizey));
}

Maze::~Maze() {}

void Maze::display() const {
  for (unsigned int i = 0; i < maze.size(); i++) {
    for (unsigned int j = 0; j < maze[i].size(); j++) {
      std::cout << maze[i][j].getSymbol();
    }
    std::cout << std::endl;
  }
}

std::vector<Case>& Maze::operator[](int index) {
  return maze[index];
}

void Maze::parcoursenlargeur(int startingx,
                             int startingy,
                             int endingx,
                             int endingy,
                             int sizex,
                             int sizey) {
  std::queue<std::pair<int, int>> q;
  std::vector<std::vector<bool>> visited(sizex,
                                         std::vector<bool>(sizey, false));

  // Vérifier si les coordonnées de départ et d'arrivée sont valides
  if (startingx < 0 || startingx >= sizex || startingy < 0 ||
      startingy >= sizey || endingx < 0 || endingx >= sizex || endingy < 0 ||
      endingy >= sizey) {
    std::cout << "Coordonnées de départ ou d'arrivée invalides." << std::endl;
    return;
  }

  // Ajouter les coordonnées de départ à la file d'attente et marquer comme
  // visité
  q.push(std::make_pair(startingx, startingy));
  visited[startingx][startingy] = true;

  while (!q.empty()) {
    // Obtenir les coordonnées du prochain nœud à visiter
    int x = q.front().first;
    int y = q.front().second;
    q.pop();

    // Vérifier si on a atteint la destination
    if (x == endingx && y == endingy) {
      std::cout << "Destination atteinte !" << std::endl;
      return;
    }

    // Parcourir les voisins du nœud actuel
    // (ici, vous devrez im plémenter votre propre logique pour déterminer les
    // voisins) Exemple : parcours des 4 directions (haut, bas, gauche, droite)
    std::vector<std::pair<int, int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (const auto& dir : directions) {
      int nx = x + dir.first;
      int ny = y + dir.second;

      // Vérifier si les coordonnées du voisin sont valides et non visitées
      if (nx >= 0 && nx < sizex && ny >= 0 && ny < sizey && !visited[nx][ny] &&
          !maze[nx][ny].getVisited() && !maze[nx][ny].getWall()) {
        // Ajouter les coordonnées du voisin à la file d'attente et marquer
        // comme visité
        q.push(std::make_pair(nx, ny));
        visited[nx][ny] = true;
      }
    }
  }

  std::cout << "Aucun chemin trouvé jusqu'à la destination." << std::endl;
}
