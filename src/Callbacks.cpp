#include "Callbacks.h"
#include "Color.h"
#include "Context.h"
#include <iostream>

using namespace std;

Callbacks::Callbacks(Context *c)
{
    this->c = c;
}

void Callbacks::squareSelectedCallBack()
{
    cout << "selected square\n";
    c->setShapeToDraw(SQUARE);
}

void Callbacks::circleSelectedCallBack()
{
    cout << "selected circle\n";
    c->setShapeToDraw(CIRCLE);
}

void Callbacks::triangleSelectedCallBack()
{
    cout << "selected triangle\n";
    c->setShapeToDraw(TRIANGLE);
}

void Callbacks::increaseLineWeightCallBack()
{
    cout << "increasing line weight\n";
    float weight = c->getLineWeight();
    if (weight > 0.5) c->setLineWeight(weight + 0.5);
}

void Callbacks::decreaseLineWeightCallBack()
{
    cout << "decreasing line weight\n";
    float weight = c->getLineWeight();
    if (weight > 0.5) c->setLineWeight(weight - 0.5);
}

void Callbacks::toggleFilledCallBack()
{
    cout << "making line filled\n";
    c->setIsFilled(!c->getIsFilled());
}

void Callbacks::changeLineColorCallBack(Color color) {
    //set the context line color
    cout << "changing the line color\n";
    c->setLineColor(color);
}

void Callbacks::changeFillColorCallBack(Color color) {
    //set the context fill color
    cout << "changing the fill color\n";
    c->setFillColor(color);
}
