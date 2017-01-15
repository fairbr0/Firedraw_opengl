#pragma once
#include "Shape.h"
#include <string>
#include <iostream>
#include "Point.h"

class Line : public Shape {
public:
    Line();
    Line(Point p1, Point p2, int objRef, Element e, string type) :
        Shape(p1, 0, 0, objRef, e, type) {
            this->end = p2;
        }
    void drawShape();
    void rotate();
    void move(float x, float y);
    void movePoint(float x, float y, bool p);
    Point getP1();
    Point getP2();


};
