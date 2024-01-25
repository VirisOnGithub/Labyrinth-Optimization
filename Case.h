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

Case::Case()
    : symbol('X'), visited(false), isWall(false), isStart(false), isEnd(false) {}

Case::~Case() {}

Case::Case(char symbol, bool visited, bool isWall, bool isStart, bool isEnd)
    : symbol(symbol), visited(visited), isWall(isWall), isStart(isStart), isEnd(isEnd) {}

char Case::getSymbol() const
{
    return symbol;
}

#endif // CASE_H
