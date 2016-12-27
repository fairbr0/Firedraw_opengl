#pragma once

#include "Shape.h"
#include "Element.h"
#include <string>

class Text : public Shape {
public:
    Text();
    Text(string s, Point p, int width, int height, int objRef, Element e, string type) : Shape(p, width, height, objRef, e, type){
        this->text = s;
    }
    void drawShape();
private:
    string text;
    void drawText(string s);
};
