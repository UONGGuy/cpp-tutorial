#include "../Creatures.h"
#include <iostream>

int main()
{
    Monster m{ Monster::Type::orc };
    std::cout << "A " << m.getName() << " (" << m.getSymbol() << ") was creatd.\n";

    return 0;
}
