#include <iostream>
#include "Case.h"

int main()
{
    Case c = Case('a', false, false, false, false);
    std::cout << c.getSymbol() << std::endl;
    return 0;
}