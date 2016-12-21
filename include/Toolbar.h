#pragma once

#include "Button.h"
#include "SwatchButton.h"
#include "StickyButton.h"
#include <vector>
#include <iostream>
#include "Context.h"

using namespace std;

class Toolbar {
public:
    Toolbar(Context *c);
    void handleClickEvent(int objRef, int state);
    void draw();

private:
    Context* c;
    int objRef, selectedRef;
    Button sqrBtn;
    Button crlBtn;
    Button triBtn;
    Button ilwBtn;
    Button dlwBtn;
    StickyButton fillBtn;
    StickyButton lcBtn;
    StickyButton fcBtn;
    vector<SwatchButton> colors;
    vector<Button*> buttons;
    Callbacks callbacks = NULL;

    void initColors();
    //****** Callback functions to update the current context *******//

};
