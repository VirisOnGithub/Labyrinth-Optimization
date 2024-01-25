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

public:
    Case();
    Case(char symbol, bool visited = false, bool isWall = false, bool isStart = false, bool isEnd = false);
    ~Case();
    char getSymbol() const;
};

#endif // CASE_H
