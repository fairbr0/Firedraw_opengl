#pragma once

class Point
{
public:
    Point();
    Point(float x, float y);
    void move(float dx, float dy);
    double getDistance(Point p);
    Point getMidPoint(Point p);
    float * getPoint();
 private:
    float point[2];
};
