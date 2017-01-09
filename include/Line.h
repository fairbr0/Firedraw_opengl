#pragma once
#include "Shape.h"
#include <string>
#include <iostream>
#include "Point.h"

class Line : public Shape {
public:
    Line();
    Line(Point p1, Point p2, int objRef, Element e, string type) :
        Shape(p1, 0, 0, this->objRef, e, type) {
            this->end = p2;
            this->geometry.push_back(p1);
            this->geometry.push_back(p2);
        }
    void drawShape();
    void rotate();
    void move(float x, float y);
    void movePoint(float x, float y, bool p);
    Point getP1();
    Point getP2();

private:
    Point end;

};
