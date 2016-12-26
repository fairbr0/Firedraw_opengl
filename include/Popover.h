#pragma once
#include <GLUT/glut.h>
#include <string>
#include <iostream>
#include "Button.h"
#include "Square.h"

class Popover {
public:
    Popover();
    Popover(void (Callbacks::*callBack_func)(), Callbacks *callbacks, string description, string title);
    virtual void display();
private:
    Square area;

};
