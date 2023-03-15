/*  points3d.cpp

    Program to hold 3d coordinates in a class.

    Members:
    - Var (pr): int m_x, int m_y, int m_z
    - Fun (pub): setValues() -> sets m_x, m_y, m_z values
                 print() -> prints values in format <m_x, m_y, m_z>
*/

#include <iostream>

class Point3d
{
    int m_x{};
    int m_y{};
    int m_z{};

public:
    void setValues(int x, int y, int z)
    {
        m_x = x;
        m_y = y;
        m_z = z;
    }

    void print()
    {
        std::cout << "<" << m_x << ", " << m_y << ", " << m_z << ">\n";
    }

    bool isEqual(const Point3d& point_compare)
    {
        return (m_x == point_compare.m_x && m_y == point_compare.m_y && m_z == point_compare.m_z);
    }
};

int main()
{
    Point3d point1;
    point1.setValues(1, 2, 3);

    Point3d point2;
    point2.setValues(1, 2, 3);

    if (point1.isEqual(point2))
    {
        std::cout << "point1 and point2 are equal\n";
    }
    else
    {
        std::cout << "point1 and point2 are not equal\n";
    }

    Point3d point3;
    point3.setValues(3, 4, 5);
    
    if (point1.isEqual(point3))
    {
        std::cout << "point1 and point3 are equal\n";
    }
    else
    {
        std::cout << "point1 and point3 are not equal\n";
    }
    return 0;
}
