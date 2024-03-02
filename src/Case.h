#ifndef CASE_H
#define CASE_H

class Case
{
private:
     char symbol;
     bool visited;
     bool isWall;
     bool isStart;
     bool isEnd;
     float distance;

public:
     Case *parent;
     Case();
     Case(char symbol,
          bool visited = false,
          bool isWall = false,
          bool isStart = false,
          bool isEnd = false);
     ~Case();
     char getSymbol() const;
     void setSymbol(char symbol);
     bool getVisited() const;
     void setStartCase();
     bool getStartCase() const;
     void setEndCase();
     bool getEndCase() const;
     void setWall();
     bool getWall() const;
     void setVisited();
     void setDistance(float distance);
     float getDistance() const;
};

#endif // CASE_H
