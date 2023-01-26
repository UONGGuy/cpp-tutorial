/*  MonsterType.cpp

    Program to instantiate a troll from an unscoped enumerated type.
    Contains monster races: orcs, goblins, trolls, ogres, skeletons.
    
    Is only supposed to compile without any problems.

*/

namespace monster
{
    enum MonsterType
    {
        orc,
        goblin,
        troll,
        ogre,
        skeleton,
    };
}

int main()
{
    monster::MonsterType monster1{ monster::troll };

    return 0;
}
