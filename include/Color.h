#pragma once
#include <stdlib.h>
#include <vector>
using namespace std;

class Color
{
public:
    Color();
    Color(float r, float g, float b);
    Color(float r, float g, float b, float a);
    vector<float> getColors();
    void setColor(float r, float g, float b, float a);
    void setAlpha(float a);
private:
    float red, green, blue, alpha;
};
