#include "Callbacks.h"
#include "Color.h"
#include "Context.h"
#include <iostream>
#include "io.h"
#include "string"

using namespace std;

//Callback functions.

//Callbacks will alter the application state machine, so context pointer is passesd.
//Callbacks must be in a separate class from context, to avoid circular dependencies
//with button, toolbar and the context
Callbacks::Callbacks(Context *c)
{
    this->c = c;
}

//callback to set the square as the current draw tool
void Callbacks::squareSelectedCallBack()
{
    c->setToolMode(DRAW);
    c->appClickedObject = NULL;
    c->resetTempShapes();
    c->setShapeToDraw(SQUARE);
}

//callback to set the circle as the current draw tool
void Callbacks::circleSelectedCallBack()
{
    c->setToolMode(DRAW);
    c->appClickedObject = NULL;
    c->resetTempShapes();
    c->setShapeToDraw(CIRCLE);
}

//callback to set the triangle as the current draw tool
void Callbacks::triangleSelectedCallBack()
{
    c->setToolMode(DRAW);
    c->appClickedObject = NULL;
    c->resetTempShapes();
    c->setShapeToDraw(TRIANGLE);
}

//callback to set the line as the current draw tool
void Callbacks::lineSelectedCallBack()
{
    c->setToolMode(DRAW);
    c->appClickedObject = NULL;
    c->resetTempShapes();
    c->setShapeToDraw(LINE);
}

//callback to increase the line weight
void Callbacks::increaseLineWeightCallBack()
{
    float weight = c->getLineWeight();
    if (weight < 10) c->setLineWeight(weight + 0.5);
}

//callback to decrease the line weight
void Callbacks::decreaseLineWeightCallBack()
{
    float weight = c->getLineWeight();
    if (weight > 0.5) c->setLineWeight(weight - 0.5);
}

//callback to toggle if shapes should be filled or not
void Callbacks::toggleFilledCallBack()
{
    c->setIsFilled(!c->getIsFilled());
}

//callback to set swatches to change the line color
void Callbacks::changeLineColorCallBack()
{
    c->colorToChange = true;
}

//callback to set swatches to change the fill color
void Callbacks::changeFillColorCallBack()
{
    c->colorToChange = false;
}

//callback to change to currently selected color
void Callbacks::changeColorCallBack(Color color)
{
    c->setColor(color);
}

//callback to delete all drawing objects
void Callbacks::clearCanvasCallBack()
{
    c->resetAppShapes();
    c->resetTempShapes();
}

//callback to delete the selected object
void Callbacks::deleteSelectedCallBack()
{
    if (c->getToolMode() == MOVE)
        c->deleteSelectedShape();
}

//callback to set the tool mode to draw
void Callbacks::selectDrawToolCallBack()
{
    c->setToolMode(DRAW);
}

//callback to set the tool mode as move
void Callbacks::selectMoveToolCallBack()
{
    c->setToolMode(MOVE);
}

//callback to start the load file process.
void Callbacks::toolbar_loadCallBack()
{
    c->setToolMode(POPOVER);
    c->setCreatePopup(LOAD_POPUP);
}

//callback to start the save file process
void Callbacks::toolbar_saveCallBack()
{
    c->setToolMode(POPOVER);
    c->setCreatePopup(SAVE_POPUP);

}

//callback to start the insert text process
void Callbacks::toolbar_textCallBack()
{
    c->setToolMode(POPOVER);
    c->setCreatePopup(TEXT_POPUP);
}

//callback to cancel a text entry popover operation
void Callbacks::popover_cancelCallBack()
{
    c->setToolMode(MOVE);
    c->redisplay();
}

//callback to save a file
void Callbacks::popover_saveCallBack(string rtn)
{
    io i(this->c);
    i.save(rtn);
    c->setToolMode(MOVE);
    c->redisplay();
}

//callback to load a file
void Callbacks::popover_loadCallBack(string rtn)
{
    io i(this->c);
    i.load(rtn);
    c->setToolMode(MOVE);
    c->redisplay();
}

//callback to insert text to the canvas
void Callbacks::popover_textCallBack(string rtn)
{
    c->setToolMode(MOVE);
    c->addText(rtn);
}


//callback to increase the alpha value of a shape
void Callbacks::increaseTransparencyCallBack()
{
    c->increaseAlpha();
}


//callback to decrease the alpha value of a shape
void Callbacks::decreaseTransparencyCallBack()
{
    c->decreaseAlpha();
}
