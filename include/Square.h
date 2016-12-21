#pragma once

#include "Shape.h"
#include "Element.h"

class Square : public Shape {
public:
    Square(Point p, int width, int height, int objRef, Element e) : Shape(p, width, height, objRef, e){
        this->geometry.push_back(Point(-0.5, -0.5));
        this->geometry.push_back(Point(0.5, -0.5));
        this->geometry.push_back(Point(0.5, 0.5));
        this->geometry.push_back(Point(-0.5, 0.5));
    }
private:
};
