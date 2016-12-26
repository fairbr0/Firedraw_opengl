#pragma once
#include "Button.h"
#include <string>
#include "Callbacks.h"

class PopoverButton : public Button {
public:
    PopoverButton();
    PopoverButton(float x, float y, float w, float h, string label, void (Callbacks::*nextCallBack_func)(string rtn), Callbacks* callbacks, int objRef) :
        Button(x, y, w, h, label, NULL, callbacks, objRef){
            this->nextCallBack = nextCallBack_func;
         }
    void (Callbacks::*nextCallBack)(string rtn);
    void callBack(string s);
private:
};
