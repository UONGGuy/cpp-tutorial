/*  randomMonsterGenerator.cpp
 *
 *  Program to generate, print and validate monster types with various
 *  attributes.
 *
 */

#include "Random_MT.h"
#include <array>
#include <string>
#include <string_view>
#include <iostream>

class Monster
{
public:
    enum class Type
    {
        dragon,
        goblin,
        ogre,
        orc,
        skeleton,
        troll,
        vampire,
        zombie,
    
        max_monster_types
    };

private:
    Type m_type{};
    std::string m_name{};
    std::string m_roar{};
    int m_hp{};

public:
    Monster(Type type, std::string name, std::string roar, int hp)
        : m_type{ type }, m_name{ name }, m_roar{ roar }, m_hp{ hp }
    {}

    std::string_view getTypeString() const
    {
        switch (m_type)
        {
            case Type::dragon: return "dragon";
            case Type::goblin: return "goblin";
            case Type::ogre: return "ogre";
            case Type::orc: return "orc";
            case Type::skeleton: return "skeleton";
            case Type::troll: return "troll";
            case Type::vampire: return "vampire";
            case Type::zombie: return "zombie";
            default: return "???";
        }
    }

    void print() const
    {
        std::cout << m_name << " the " << getTypeString() << " has " << m_hp << " hit points and says " << m_roar << '\n';
    }
};

namespace MonsterGenerator
{

    Monster generate()
    {
        auto type{ static_cast<Monster::Type>(Random::get(0, static_cast<int>(Monster::Type::max_monster_types) - 1)) };
        int hp{ Random::get(1, 100) };

        // static to avoid reinitialisation every time this fn called
        static constexpr std::array s_names{ "Blarg", "Moog", "Pksh", "Tyrn", "Mort", "Hans" };
        static constexpr std::array s_roars{ "*ROAR*", "*peep*", "*squeal*", "*whine*", "*hum*", "*burp*" };

        auto name{ s_names[Random::get(0, static_cast<int>(s_names.size() - 1))] };
        auto roar{ s_roars[Random::get(0, static_cast<int>(s_names.size() - 1))] };
        return Monster { type, name, roar, hp };
    }
};

int main()
{
    Monster m{ MonsterGenerator::generate() };
    m.print();

    return 0;
}
