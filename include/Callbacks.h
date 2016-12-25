//#include "Context.h"
#pragma once

#include "Color.h"
#include "Context.h"

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
    void loadCallBack();
    void saveCallBack();
    Context *c;
private:
    //Context c;
};
