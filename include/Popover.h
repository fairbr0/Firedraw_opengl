#pragma once
#include <string>
#include "Callbacks.h"
#include "Context.h"
#include "Button.h"
#include "PopoverButton.h"

using namespace std;

class Popover {
public:
    Popover();
    Popover(Context *cont, Callbacks* c, void (Callbacks::*callBack_func)(string), void (Callbacks::*cancelFunc)(), string buttonLabel, string windowTitle, string windowDescription);
    void display();
    void handleClickEvent(int objRef, int state);
    void addChar(unsigned char c);
private:
    string buttonLabel;
    string windowTitle;
    string windowDescription;
    Callbacks callbacks = NULL;
    Button cancelBtn;
    PopoverButton nextBtn;
    Context* context;
    bool textAreaSelected = false;
    string inputText;

    void drawText(string s);
    void deselectAll();

};
