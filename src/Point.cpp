#include "Point.h"

Point::Point()
{
    //ctor
    float x = 0;
    float y = 0;
    float z = 0;
}

Point::~Point()
{
    //dtor
}

Point::Point(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}
