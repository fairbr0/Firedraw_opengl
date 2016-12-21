#pragma once
#include <vector>
#include <string>
#include "Point.h"
#include "Callbacks.h"

typedef void (*ButtonCallBack)();

class Button
{
public:
    Button();
    Button(float x, float y, float w, float h, std::string label, void (Callbacks::*callBack_func)(), Callbacks* callbacks, int objRef);
    float x, y, w, h;
    std::string label;
    bool isClicked, isHovered;
    int objRef;
    std::vector<Point> geometry;
    void (Callbacks::*callBack_func)();
    void drawButton();
    void makeGeometry();
    void whoami();
    void callBack();
    Callbacks* callbacks;
private:
};
