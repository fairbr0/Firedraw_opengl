#pragma once

#include "Shape.h"

class Square : public Shape {
public:
    Square(Point p, int width, int height, int objRef) : Shape(p, width, height, objRef){
        this->geometry.push_back(Point(-0.5, -0.5));
        this->geometry.push_back(Point(0.5, -0.5));
        this->geometry.push_back(Point(0.5, 0.5));
        this->geometry.push_back(Point(-0.5, 0.5));
    }
private:
};
