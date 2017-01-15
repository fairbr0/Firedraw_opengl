#include "Point.h"
#include <cmath>

//Basic point class, used throughout to draw shapes and lines to screen.

Point::Point()
{
    this->point[0] = 0.0f;
    this->point[1] = 0.0f;
}

Point::Point(float x, float y)
{
    this->point[0] = x;
    this->point[1] = y;
}

void Point::move(float dx, float dy)
{
    this->point[0] = dx;
    this->point[1] = dy;
}

float * Point::getPoint()
{
    return point;
}

double Point::getDistance(Point p)
{
    int dx = this->point[0] - p.getPoint()[0];
    int dy = this->point[1] - p.getPoint()[1];
    return sqrt(dx * dx + dy * dy);
}

Point Point::getMidPoint(Point p) {
    int nx = (p.getPoint()[0] + this->point[0]) / 2;
    int ny = (p.getPoint()[1] + this->point[1]) / 2;
    return Point(nx, ny);
}
