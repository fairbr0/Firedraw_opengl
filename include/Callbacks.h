//#include "Context.h"
#pragma once

#include "Color.h"
#include "Context.h"
#include <string>

class Callbacks
{
public:
    Callbacks(Context *c);
    void increaseLineWeightCallBack();
    void decreaseLineWeightCallBack();
    void toggleFilledCallBack();
    void changeColorCallBack(Color c);
    void changeLineColorCallBack();
    void changeFillColorCallBack();
    void squareSelectedCallBack();
    void triangleSelectedCallBack();
    void circleSelectedCallBack();
    void clearCanvasCallBack();
    void selectDrawToolCallBack();
    void selectMoveToolCallBack();
    void deleteSelectedCallBack();
    void toolbar_loadCallBack();
    void toolbar_saveCallBack();
    void toolbar_textCallBack();
    void increaseTransparencyCallBack();
    void decreaseTransparencyCallBack();
    void popover_cancelCallBack();
    void popover_saveCallBack(string rtn);
    void popover_loadCallBack(string rtn);
    void popover_textCallBack(string rtn);
    Context *c;
private:
};
