#include "Callbacks.h"
#include "Color.h"
#include "Context.h"
#include <iostream>
#include "io.h"
#include "string"

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

void Callbacks::lineSelectedCallBack()
{
    c->setToolMode(DRAW);
    c->setShapeToDraw(LINE);
}

void Callbacks::increaseLineWeightCallBack()
{
    cout << "increasing line weight\n";
    float weight = c->getLineWeight();
    if (weight < 10) c->setLineWeight(weight + 0.5);
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

void Callbacks::toolbar_loadCallBack()
{
    c->setToolMode(POPOVER);
    c->setCreatePopup(LOAD_POPUP);
}

void Callbacks::toolbar_saveCallBack()
{
    c->setToolMode(POPOVER);
    c->setCreatePopup(SAVE_POPUP);

}
void Callbacks::toolbar_textCallBack()
{
    c->setToolMode(POPOVER);
    c->setCreatePopup(TEXT_POPUP);
}

void Callbacks::popover_cancelCallBack()
{
    std::cout << "In cancel callback\n";
    cout << "c ref " << c << "\n";
    c->setToolMode(MOVE);
    c->redisplay();
}

void Callbacks::popover_saveCallBack(string rtn)
{
    io i(this->c);
    i.save(rtn);
    c->setToolMode(MOVE);
    c->redisplay();
}

void Callbacks::popover_loadCallBack(string rtn)
{
    io i(this->c);
    i.load(rtn);
    c->setToolMode(MOVE);
    c->redisplay();
}

void Callbacks::popover_textCallBack(string rtn)
{
    c->setToolMode(MOVE);
    c->addText(rtn);
}

void Callbacks::increaseTransparencyCallBack()
{
    c->increaseAlpha();
}

void Callbacks::decreaseTransparencyCallBack()
{
    c->decreaseAlpha();
}
