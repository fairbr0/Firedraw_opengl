#include "Element.h"
#include <string>

Element::Element()
{
    lineWeight = 2.0;
    lineColor = Color();
    fillColor = Color();
    isFilled = true;
}

Element::Element(bool isFilled, float lineWeight, Color lineColor, Color fillColor)
{
    this->isFilled = isFilled;
    this->lineColor = lineColor;
    this->fillColor = fillColor;
    this->lineWeight = lineWeight;
}

void Element::setIsFilled(bool b)
{
    this->isFilled = b;
}

void Element::setLineColor(Color c)
{
    this->lineColor = c;
}

void Element::setFillColor(Color c)
{
    this->fillColor = c;
}

void Element::setLineWeight(float weight)
{
    this->lineWeight = weight;
}

bool Element::getIsFilled()
{
    return this->isFilled;
}

float Element::getLineWeight()
{
    return this->lineWeight;
}

Color Element::getLineColor()
{
    return this->lineColor;
}

Color Element::getFillColor()
{
    return this->fillColor;
}

string Element::toString()
{
    return "";
}
    /*
    stringstream rtn;
    rtn << "Filled: " << this->isFilled << "\n";
    rtn << "Line Col: " << this->lineColor.getColors()[0] << ", " << this->lineColor.getColors()[1] << ", " << this->lineColor.getColors()[2] << ", " << this->lineColor.getColors()[3] << "\n";
    rtn << "Fill Col: " << this->fillColor.getColors()[0] << ", " << this->fillColor.getColors()[1] << ", " << this->fillColor.getColors()[2] << ", " << this->fillColor.getColors()[3] << "\n";
    rtn << "Line Weight: " << this->lineWeight << "\n";
    return rtn.str();
}*/
