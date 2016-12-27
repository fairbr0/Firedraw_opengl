#pragma once

#include "Point.h"
#include "Element.h"
#include <vector>
#include <string>

class Shape : public Element {
public:
    Shape();
    Shape(Point p, int w, int h, int objRef, Element e, string type);
    Shape(Point p, int w, int h, int objRef, string type);
    Point getCenter();
    float getRotation();
    int getWidth();
    int getHeight();
    int getObjRef();
    void setRotation(double r);
    void setCenter(Point p);
    void setSize(int width, int height);
    void move(float x, float y);
    void drawShape();
    Element elem;
    string toString();
    string getType();
private:

protected:
    std::vector<Point> geometry;
    Point center;
    int width;
    int height;
    float rotation;
    int objRef;
    string type;
};
