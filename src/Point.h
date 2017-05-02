#ifndef POINT_H
#define POINT_H

#include <typeinfo>
#include <assert.h>
class Point{
public:
    double x;
    double y;
    
    bool operator==(Point const& a);

	Point();
	~Point();
	Point(double x, double y);
    void resgressionTest();
};



#endif // POINT_H
