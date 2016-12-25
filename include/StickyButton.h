#pragma once
#include "Button.h"
#include <string>
#include "Callbacks.h"

class StickyButton : public Button {
public:
    StickyButton();
    StickyButton(float x, float y, float w, float h, std::string label, void (Callbacks::*callBack_func)(), Callbacks* callbacks, int objRef)
        : Button(x, y, w, h, label, callBack_func, callbacks, objRef) { }
    void toggleEnabled();
    void setEnabled(bool b);
    bool isEnabled();
    void drawButton();
    void callBack();
private:
    bool enabled = false;
};
