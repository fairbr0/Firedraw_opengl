#pragma once

#include "Shape.h"
#include "Element.h"
#include <string>

class Triangle : public Shape {
public:
    Triangle(Point p, int width, int height, int objRef, Element e, string type) : Shape(p, width, height, objRef, e, type){
        this->geometry.push_back(Point(-0.5, -0.5));
        this->geometry.push_back(Point(0.0, 0.5));
        this->geometry.push_back(Point(0.5, -0.5));
    };
private:
};
