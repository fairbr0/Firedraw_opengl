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
    void changeLineColorCallBack(Color c);
    void changeFillColorCallBack(Color c);
    void squareSelectedCallBack();
    void triangleSelectedCallBack();
    void circleSelectedCallBack();
    Context *c;
private:
    //Context c;
};
