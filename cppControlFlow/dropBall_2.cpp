/*  dropBall_2.cpp

    Program to track height of ball as it falls until it hits
    the ground.
    
    INPUT: height (in metres)

    OUTPUT: time (in seconds)
*/

#include <iostream>
#include "constants.h"

double calculateHeight(double initialHeight, int seconds);

int main()
{
    std::cout << "Enter the initial height of the tower in metres: ";
    double initialHeight {};
    std::cin >> initialHeight;
    
    int timeElapsed { 0 };
    double heightNow { initialHeight };

    while (heightNow > 0.0)
    {
        heightNow = calculateHeight(initialHeight, timeElapsed);
        std::cout << "At " << timeElapsed << " seconds, the ball is at height: " << heightNow << "\n";
        ++timeElapsed;
    }

    return 0;
}

double calculateHeight(double initialHeight, int seconds)
{
    double distanceFallen { myConstants::gravity * seconds * seconds / 2 };
    double heightNow { initialHeight - distanceFallen };

    // Check if height is negative
    // If so, set height to ground-level

    if (heightNow < 0)
        return 0.0;
    else
        return heightNow;
}

