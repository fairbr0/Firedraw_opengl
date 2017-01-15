#include "Color.h"
#include <stdlib.h>
#include <vector>

using namespace std;

Color::Color()
{
    red = 0.0f; green = 0.0f; blue = 0.0f; alpha = 1.0f;
}

//create a solid color
Color::Color(float r, float g, float b)
{
    red = r;
    green = g;
    blue = b;
    alpha = 1.0f;
}

//create color with desired transparency
Color::Color(float r, float g, float b, float a)
{
    red = r;
    green = g;
    blue = b;
    alpha = a;
}

//return a vector of colors
vector<float> Color::getColors()
{
    vector<float> vals;
    vals.push_back(red);
    vals.push_back(green);
    vals.push_back(blue);
    vals.push_back(alpha);
    return vals;
}

//change the color
void Color::setColor(float r, float g, float b, float a)
{
    red = r;
    green = g;
    blue = b;
    alpha = a;
}

//set the transparency
void Color::setAlpha(float a)
{
    this->alpha = a;
}
