/*  ball.cpp

    Program containing class Ball that holds the colour and radius of
    a ball.

*/

#include <iostream>
#include <string_view>

class Ball
{
private:
    std::string_view m_colour{};
    double m_radius{};

public:

    Ball(std::string_view colour="black", double radius = 10.0)
    {
        m_colour = colour;
        m_radius = radius;
    }

    Ball(double radius, std::string_view colour="black")
    {
        m_colour = colour;
        m_radius = radius;
    }

    void print()
    {
        std::cout << "colour: " << m_colour << ", radius: " << m_radius << std::endl;
    }
};

int main()
{
    Ball def{};
    def.print();

    Ball blue{ "blue" };
    blue.print();

    Ball twenty{ 20.0 };
    twenty.print();

    Ball blueTwenty{ "blue", 20.0 };
    blueTwenty.print();

    return 0;
}

