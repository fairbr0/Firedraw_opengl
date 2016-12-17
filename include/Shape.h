#pragma once

#include "Point.h"
#include "Element.h"
#include <vector>

class Shape : public Element {
public:
    Shape();
    Shape(Point p, int w, int h, int objRef);
    Point getCenter();
    double getRotation();
    int getWidth();
    int getHeight();
    int getObjRef();
    void setRotation(double r);
    void move(float x, float y);
    void setCenter(Point p);
    void setSize(int width, int height);
    void drawShape();
private:
    Point center;
    int width;
    int height;
    double rotation;
    int objRef;
protected:
    std::vector<Point> geometry;
};
