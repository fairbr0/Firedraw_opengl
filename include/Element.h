#pragma once

#include "Color.h"

class Element
{
public:
    Element();
    Element(bool isFilled, float lineWeight, Color lineColor, Color fillColor);
    void setIsFilled(bool b);
    void setLineColor(Color c);
    void setFillColor(Color c);
    void setLineWeight(float weight);
    float getLineWeight();
    Color getLineColor();
    Color getFillColor();
    bool getIsFilled();
protected:
    Color lineColor;
    Color fillColor;
    float lineWeight;
    bool isFilled;
};
