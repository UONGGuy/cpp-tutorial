#include "Creatures.h"
#include "Items.h"
#include "Random_MT.h"
#include <iostream>
#include <stdexcept>
#include <string>

std::string getPlayerName()
{
    std::cout << "Enter Player name: ";
    std::string name{};
    std::cin >> name;
    std::cout << "Welcome, " << name << '\n';

    return name;
}

void attackMonster(Player& player, Monster& monster)
{
    monster.reduceHealth(player.getDmgPerHit());
    std::cout << "You hit the " << monster.getName() << " for " << player.getDmgPerHit() << " damage.\n";
    if (monster.isDead())
    {
        player.levelUp();
        std::cout << "You are now level " << player.getLevel() << '\n';
        
        player.addGold(monster.getGold());
        std::cout << "You have found " << monster.getGold() << " gold.\n";
    }
}

void attackPlayer(Player& player, Monster& monster)
{
    player.reduceHealth(monster.getDmgPerHit());
    std::cout << "The " << monster.getName() << " hit you for " << monster.getDmgPerHit() << " damage.\n";
    if (player.isDead())
    {
        std::cout << "You died at level " << player.getLevel() << " with " << player.getGold() << " gold.\n";
        std::cout << "Too bad you can't take it with you!\n";
    }
}

void findPotion(Player& player)
{
    int findPotion{ RandomMT::getRandomInt(1, 10) };
    if (findPotion <= 3)
    {
        std::cout << "You found a mythical potion! Do you want to drink it? [y/n]: ";
        char action{};
        std::cin >> action;

        if (action == 'y' || action == 'Y')
        {
            Potion potion{ Potion::getRandomPotion() };
            player.drinkPotion(potion);
            std::cout << "You drank a " << potion.getSize() << " potion of " << potion.getType() << ".\n";

            if (player.isDead())
            {
                std::cout << "You died at level " << player.getLevel() << " with " << player.getGold() << " gold.\n";
                std::cout << "Too bad you can't take it with you!\n";
            }
        }
    }
}

void showPlayerStats(Player& player)
{
    std::cout << "\n Player hp: " << player.getHp() << "\t Player dmg: " << player.getDmgPerHit() << '\n';
}

void fightMonster(Player& player)
{
    Monster monster{ Monster::getRandomMonster() };
    std::cout << "You have encountered a " << monster.getName() << " (" << monster.getSymbol() << ").\n";

    bool fleeSuccess{};

    do 
    {
        std::cout << "(R)un or (F)ight: ";
        char action{};
        std::cin >> action;

        if (action == 'f' || action == 'F')
        {
            attackMonster(player, monster);
            if (!monster.isDead())
            {
                attackPlayer(player, monster);
            }
        }
        else
        {
            fleeSuccess = static_cast<bool>(RandomMT::getRandomInt(0, 1));
            if (fleeSuccess)
                break;
            attackPlayer(player, monster);
        }
    }
    while (!player.isDead() && !monster.isDead() && !fleeSuccess);    

    if (!player.isDead() && monster.isDead())
    {
        findPotion(player);
    }

}

int main()
{
    Player player{ getPlayerName() };

    while (!player.isDead() && !player.hasWon())
    {
        fightMonster(player);
    }

    if (player.hasWon())
    {
        std::cout << "Congratulations! You won the game with " << player.getGold() << " gold!\n";
    }

    return 0;
}
