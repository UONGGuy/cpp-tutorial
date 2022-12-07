/*  hi_lo.cpp
    
    Program to play a game of hi-lo.
    Program chooses a random integer from 1-100.
    User has 7 tries to guess the number.
    Program tells user if guess is too high, too low, or correct.
    After 7 tries, answer is revealed.
    User is then asked to play again (y/n).
*/

#include <iostream>
#include <random>

void clearBuffer()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int guessInput()
{
    while (true)
    {
        int x{};
        std::cin >> x;
        clearBuffer();
        if (x >= 1 && x <= 100)
        {
            return x;
        }
        else 
        {
            if (std::cin.fail())
            {
                std::cin.clear();
                clearBuffer();
            }
            std::cout << "Guesses must be integers from 1 - 100. Try again: ";
        }
    }   
}

void playGame(int guesses, int targetValue)
{
    std::cout << "Let's play a game. I'm thinking of a number between 1 and 100. You have 7 tries to guess what it is.\n";

    int guessNumber { 1 };
    
    while (guessNumber <= guesses)
    {
        std::cout << "Guess #" << guessNumber << ": ";
        int guessValue { guessInput() };
        if (guessValue == targetValue)
        {
            std::cout << "Correct! You win!\n";
            return;
        }
        else if (guessValue < targetValue)
        {
            std::cout << "Your guess is too low.\n";
        }
        else if (guessValue > targetValue)
        {
            std::cout << "Your guess is too high.\n";
        }
        ++guessNumber;
    }
    
    std::cout << "Sorry, you lose. The correct number was " << targetValue << ".\n";
}

bool playAgain()
{
    while (true)
    {
        char choice {};
        std::cout << "Would you like to play again (y/n)? ";
        std::cin >> choice;
        clearBuffer();
        
        switch (choice)
        {
            case 'y':
                return true;
            case 'n':
                return false;
        }
    }
}

int main()
{
    std::random_device rd;
    std::seed_seq ss { rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    std::mt19937 mt { ss };

    std::uniform_int_distribution<> die100 { 1, 100 };

    constexpr int guesses { 7 };
    
    bool play { true };
    while (play == true)
    {
        playGame(guesses, die100(mt));
        play = playAgain();
    }
    std::cout << "Thank you for playing.\n";
    
    return 0;
}
