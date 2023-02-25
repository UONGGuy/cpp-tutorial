/*  squareNumbers.cpp

    Program to play a game with square numbers.

    RULES
    - User inputs a number to start at and an amount of numbers to
    generate.
    - From this, generate a list of square numbers in the given range.
    - Generate a random integer from 2 to 4 and multiply each sqaure
    number by this value.
    - User must guess which numbers have been generated.
    - If user is correct, remove guessed number from list
    - If user is wrong, game is over and program prints number closest
    to user's final guess if final guess was not off by more than 4.

    TIPS
    - Use std::find to search for number in list
    - Use std::vector::erase to remove an element
    - Use std::min_element + almbda to find number closest to user's 
    guess
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <cmath>

using NumberList = std::vector<int>;

namespace config
{
    constexpr int multiplierMin{ 2 };
    constexpr int multiplierMax{ 4 };
    constexpr int errorRange{ 4 };
}

int getRandomInt(int min, int max)
{
    static std::mt19937 mt{
        static_cast<std::mt19937::result_type>(std::time(nullptr))
    };

    return std::uniform_int_distribution{ min, max }(mt);
}

NumberList generateValues(int startNum, int range, int multiplier)
{
    NumberList listOfValues(static_cast<NumberList::size_type>(range));

    int n{ startNum };

    for (auto& value : listOfValues)
    {
        value = multiplier * n * n;
        ++n;
    }

    return listOfValues;
}

NumberList initialiseGame()
{
    std::cout << "Enter a start number: ";
    int startNum{};
    std::cin >> startNum;

    std::cout << "Enter an amount of numbers to generate: ";
    int range{};
    std::cin >> range;

    int multiplier{ getRandomInt(config::multiplierMin, config::multiplierMax) };
    std::cout << "What are the values of these square numbers multiplied by " << multiplier << "?\n";

    return generateValues(startNum, range, multiplier);
}

int getUserGuess()
{
    int guess{};

    std::cout << "> ";
    std::cin >> guess;

    return guess;
}

bool findAndRemove(NumberList& values, int guess)
{
    auto found{ std::find(values.begin(), values.end(), guess) };

    if (found == values.end())
        return false;
    else
    {
        values.erase(found);
        return true;
    }
}

int findClosestValue(const NumberList& values, int guess)
{
    return *std::min_element(values.begin(), values.end(),
        [=](int a, int b) {
            return (std::abs(a - guess) < std::abs(b - guess));
    });
}

void printSuccess(NumberList::size_type remainingValues)
{
    std::cout << "Nice! ";

    if (remainingValues == 0)
    {
        std::cout << "You found all numbers, good job!\n";
    }
    else
    {
        std::cout << remainingValues << " number(s) left!\n";
    }
}

void printFailure(const NumberList& values, int guess)
{
    std::cout << guess << " is wrong!\n";

    int closestValue{ findClosestValue(values, guess) };

    if (std::abs(guess - closestValue) <= config::errorRange)
    {
        std::cout << "Try " << closestValue << " next time!\n";
    }
}

bool playRound(NumberList& values)
{
    int guess{ getUserGuess() };

    if (findAndRemove(values, guess))
    {
        printSuccess(values.size());
        return !values.empty();
    }
    else
    {
        printFailure(values, guess);
        return false;
    }
}

int main()
{
    NumberList values{ initialiseGame() };

    while (playRound(values));

    return 0;
}
