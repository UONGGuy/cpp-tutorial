/*  movePoint.cpp
 *
 *  Program to implement the Point3d and Vector3d classes in order to 
 *  translate a given (x, y, z) coordinate held by Point3d by the vector
 *  held by Vector3d.
 */

#include "Point3d.h"
#include "Vector3d.h"

int main()
{
    Point3d p{ 1.0, 2.0, 3.0 };
    Vector3d v{ 2.0, 2.0, -3.0 };

    p.print();
    p.moveByVector(v);
    p.print();

    return 0;
}
