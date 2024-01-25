#include "Case.h"

Case::Case()
    : symbol('O'), visited(false), isWall(false), isStart(false), isEnd(false) {}

Case::~Case() {}

Case::Case(char symbol, bool visited, bool isWall, bool isStart, bool isEnd)
    : symbol(symbol), visited(visited), isWall(isWall), isStart(isStart), isEnd(isEnd) {}

char Case::getSymbol() const
{
    return symbol;
}