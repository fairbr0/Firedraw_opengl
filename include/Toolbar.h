#pragma once

#include "Button.h"
#include "SwatchButton.h"
#include "StickyButton.h"
#include <vector>
#include <iostream>
#include "Context.h"
#include "Square.h"

using namespace std;

class Toolbar {
public:
    Toolbar(Context *c, int height, int width);
    void handleClickEvent(int objRef, int state);
    void draw();
    void deselectAll();
    void setDrawMode();
    void setMoveMode();
    Callbacks callbacks = NULL;
private:
    Context* c;
    int objRef, selectedRef, top, right;
    Button sqrBtn, crlBtn, triBtn, ilwBtn, dlwBtn, txtBtn, itBtn, lneBtn, clrBtn, sveBtn, opnBtn, delBtn;
    Button dtBtn;
    Square lcBox, fcBox;
    StickyButton fillBtn,lcBtn, fcBtn, mveBtn, drwBtn;
    vector<SwatchButton> colors;
    vector<Button*> buttons;
    vector<StickyButton*> stickyButtons;
    int initColors(int offset);
    void drawTitle(int offset, string text);

};
