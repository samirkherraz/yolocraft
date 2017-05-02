#include <iostream>

#include "Point.h"

using namespace std;

bool Point::operator==(Point const& a)
{
    return (x == a.x && y == a.y);
}

Point::Point()
{
    this->x = 0;
    this->y = 0;
}

Point::Point(double x, double y)
{
    

    this->x = x;
    this->y = y;
}

Point::~Point()
{   

    this->x = 0;
    this->y = 0;
}

void Point::resgressionTest()
{
    cout << "Regression test for Point class" << endl;
    if(typeid(x) == typeid(double))
        cout << "Point.x is ok" << endl;
    if(typeid(y) == typeid(double))
        cout << "Point.y is ok" << endl;
}
