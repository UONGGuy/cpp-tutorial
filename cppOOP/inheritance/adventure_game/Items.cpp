#include "Items.h"
#include "Random_MT.h"
#include <array>
#include <cassert>
#include <string_view>
#include <utility>
/*
 * Potion class
 */

const std::pair<Potion::HP, Potion::DMG> Potion::getDefaultEffect(Type type, Size size)
{
    static const std::array<
        std::array<
            std::pair<Potion::HP, Potion::DMG>
            , static_cast<std::size_t>(Size::max_potion_size)>
        , static_cast<std::size_t>(Type::max_potion_type)> 
        potionData{
        { { std::make_pair(2, 0), std::make_pair(2, 0), std::make_pair(5, 0) },          // health
          { std::make_pair(0, 1), std::make_pair(0, 1), std::make_pair(0, 1) },          // strength
          { std::make_pair(-1, 0), std::make_pair(-1, 0), std::make_pair(-1, 0) } }      // poison
    };

    return potionData.at(static_cast<std::size_t>(type)).at(static_cast<std::size_t>(size));
}

Potion::Potion(Type t, Size s)
{
    type = t;
    size = s;
    std::pair<HP, DMG> effect{ getDefaultEffect(type, size) };
    hp = effect.first;
    dmg = effect.second;
}

Potion Potion::getRandomPotion()
{
    int n_type{ RandomMT::getRandomInt(0, static_cast<int>(Type::max_potion_type - 1)) };
    int n_size{ RandomMT::getRandomInt(0, static_cast<int>(Size::max_potion_size - 1)) };
    Type type{ static_cast<Type>(n_type) };
    Size size{ static_cast<Size>(n_size) };

    return Potion{ type, size };
}

std::string_view Potion::getType() const
{
    switch(type)
    {
        case health:    return "health";
        case strength:  return "strength";
        case poison:    return "poison";
    }
    assert(0 && "Potion::Type invalid");
    return "???";
}

std::string_view Potion::getSize() const
{
    switch(size)
    {
        case small:     return "small";
        case medium:    return "medium";
        case large:     return "large";
    }
    assert(0 && "Potion::Size invalid");
    return "???";
}
