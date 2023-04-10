#ifndef ITEMS_H
#define ITEMS_H

#include <string_view>
#include <utility>

class Potion 
{
public:
    enum Type 
    {
        health,
        strength,
        poison,

        max_potion_type
    };

    enum Size 
    {
        small,
        medium,
        large,

        max_potion_size
    };

    using HP = int;
    using DMG = int;

private:
    Type type{};
    Size size{};
    HP hp{ 0 };
    DMG dmg{ 0 };

    // list of potion effects on HP and DMG
    static const std::pair<HP, DMG> getDefaultEffect(Type type, Size size);

public:
    Potion(Type type, Size size);

    static Potion getRandomPotion();
    int getHP() const { return hp; }
    int getDMG() const { return dmg; }
    std::string_view getType() const;
    std::string_view getSize() const;
};

#endif
