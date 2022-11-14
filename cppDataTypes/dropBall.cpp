/*  dropBall.cpp

    Program to simulate ball dropped off a tower on Earth.
    Ball is dropped at rest from tower of chosen height.
    Tracks ball height over 5 seconds in intervals of 1 second.
    Ball cannot go throught the ground (i.e. lower than 0 m).
    
    INPUT: double tower_height;

        FORMULA: dist_fallen = grav_accel * time_passed ** 2 / 2

    OUTPUT: dist_fallen at times 0, 1, 2, 3, 4, 5 seconds.

*/

#include<iostream>
#include<math.h>

double getTowerHeight();
double currentHeight(double towerHeight, double time);
void ballTracker(double towerHeight, double time);

int main()
{
    /*
    getTowerHeight()
    while loop -> distFallen(tower_height, time)
        distFallen:
            if formula > 0 -> print bal at formula dist
            else print ball on ground
    */
    
    double towerHeight { getTowerHeight() };
    double time {0.0};

    while(time < 6.0)
    {
        ballTracker(towerHeight, time);
        time++;
    }

    return 0;
}

double getTowerHeight()
{
    std::cout << "Enter the height of the tower in metres: ";
    double towerHeight {};
    std::cin >> towerHeight;

    return towerHeight;
}

double currentHeight(double towerHeight, double time)
{
    constexpr double grav_const {9.8};
    double dist_travelled { grav_const * pow(time, 2) / 2 };
    double ball_height { towerHeight - dist_travelled };

    return ball_height;
}

void ballTracker(double towerHeight, double time)
{
    double ball_height { currentHeight(towerHeight, time) };
    
    if (ball_height >= 0.0)
    {
        std::cout << "At " << time << " seconds, the ball is at height: " << ball_height << " metres.\n";
    }
    else
    {
        std::cout << "At " << time << " seconds, the ball is on the ground.\n";
        
    }
}
