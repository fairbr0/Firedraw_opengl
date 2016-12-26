#include "Callbacks.h"
#include "Color.h"
#include "Context.h"
#include <iostream>
#include "io.h"

using namespace std;

Callbacks::Callbacks(Context *c)
{
    this->c = c;
}

void Callbacks::squareSelectedCallBack()
{
    cout << "selected square\n";
    c->setToolMode(DRAW);
    c->setShapeToDraw(SQUARE);
}

void Callbacks::circleSelectedCallBack()
{
    cout << "selected circle\n";
    c->setToolMode(DRAW);
    c->setShapeToDraw(CIRCLE);
}

void Callbacks::triangleSelectedCallBack()
{
    cout << "selected triangle\n";
    c->setToolMode(DRAW);
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

void Callbacks::changeLineColorCallBack()
{
    //set the context line color
    cout << "changing the line color\n";
    c->colorToChange = true;
}

void Callbacks::changeFillColorCallBack()
{
    //set the context line color
    cout << "changing the fill color\n";
    c->colorToChange = false;
}

void Callbacks::changeColorCallBack(Color color)
{
    //set the context fill color
    cout << "changing the fill color\n";
    c->setColor(color);
}

void Callbacks::clearCanvasCallBack()
{
    c->resetAppShapes();
    c->resetTempShapes();
}

void Callbacks::deleteSelectedCallBack()
{
    if (c->getToolMode() == MOVE)
        c->deleteSelectedShape();
}

void Callbacks::selectDrawToolCallBack()
{
    c->setToolMode(DRAW);
}

void Callbacks::selectMoveToolCallBack()
{
    c->setToolMode(MOVE);
}

void Callbacks::loadCallBack()
{
    io i(this->c);
    i.load();
}

void Callbacks::saveCallBack()
{
    io i(this->c);
    i.save();
}

void Callbacks::increaseTransparencyCallBack()
{
    c->increaseAlpha();
}

void Callbacks::decreaseTransparencyCallBack()
{
    c->decreaseAlpha();
}
