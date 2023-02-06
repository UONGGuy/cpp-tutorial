/*  maxScore.cpp

    Program to hold the index of and print the largest score.

*/

#include <iostream>
#include <iterator> // for std::size

int main()
{
    constexpr int scores[]{ 84, 92, 76, 81, 56 };

    int maxIndex{ 0 };

    for (int student{ 1 }; student < static_cast<int>(std::size(scores)); ++student)
    {
        if (scores[student] > scores[maxIndex])
        {
            maxIndex = student;
        }
    }

    std::cout << "The best score was " << scores[maxIndex] << "\n";

    return 0;
}
