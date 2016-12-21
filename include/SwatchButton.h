#pragma once
#include "Button.h"
#include <string>
#include "Color.h"
#include "Callbacks.h"

class SwatchButton : public Button {
public:
    SwatchButton();
    SwatchButton(float x, float y, float w, float h, void (Callbacks::*swatchCallBack_func) (Color c), Callbacks* callbacks, int objRef, Color color) :
        Button(x, y, w, h, "", NULL, callbacks, objRef){
            this->color = color;
            this->swatchCallBack_func = swatchCallBack_func;
         }
    void drawButton();
    Color getColor();
    void (Callbacks::*swatchCallBack_func)(Color c);
    void swatchCallBack();
private:
    Color color;
};
