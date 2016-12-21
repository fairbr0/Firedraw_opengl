#include "Toolbar.h"
#include "Button.h"
#include <vector>
#include <iostream>
#include <GLUT/glut.h>
#include "Callbacks.h"
#include "StickyButton.h"
#include "SwatchButton.h"
#include "Context.h"

using namespace std;

Toolbar::Toolbar(Context *c)
{
    this->c = c;
    this->callbacks = Callbacks(c);
    this->objRef = 1000000;
    this->sqrBtn = Button(50, 570, 80, 40, "Square", &Callbacks::squareSelectedCallBack, &callbacks, this->objRef++);
    this->crlBtn = Button(50, 520, 80, 40, "Circle", &Callbacks::circleSelectedCallBack, &callbacks, this->objRef++);
    this->triBtn = Button(50, 470, 80, 40, "Triangle", &Callbacks::triangleSelectedCallBack, &callbacks, this->objRef++);
    this->dlwBtn = Button(25, 420, 40, 40, "-", &Callbacks::decreaseLineWeightCallBack, &callbacks, this->objRef++);
    this->ilwBtn = Button(75, 420, 40, 40, "+", &Callbacks::increaseLineWeightCallBack, &callbacks, this->objRef++);
    this->fillBtn = StickyButton(50, 370, 80, 40, "Filled", &Callbacks::toggleFilledCallBack, &callbacks, this->objRef++);
    this->lcBtn = StickyButton(25, 320, 40, 40, "Line", NULL, &callbacks, this->objRef++);
    this->fcBtn = StickyButton(75, 320, 40, 40, "Fill", NULL, &callbacks, this->objRef++);

    buttons.push_back(&sqrBtn);
    buttons.push_back(&triBtn);
    buttons.push_back(&crlBtn);
    buttons.push_back(&ilwBtn);
    buttons.push_back(&dlwBtn);
    buttons.push_back(&fillBtn);
    buttons.push_back(&lcBtn);
    buttons.push_back(&fcBtn);

    this->initColors();
}

void Toolbar::draw()
{
    //fucker below causes a seg fault. no clue why
    for (int i = 0; i < buttons.size(); i++) {
        if (buttons[i]) {
            (buttons[i])->drawButton();
        }
    }
    for (int i = 0; i < colors.size(); i++) {
        colors[i].drawButton();
    }
}

void Toolbar::handleClickEvent(int objRef, int state)
{
    selectedRef = objRef;
    for (int i = 0; i < buttons.size(); i++) {
        if ((buttons[i])->objRef == objRef) {
            if (state == GLUT_DOWN) {
                (buttons[i])->isClicked = true;
                glutPostRedisplay();
                return;
            } else {
                (buttons[i])->isClicked = false;
                (buttons[i])->callBack();
                glutPostRedisplay();
                return;
            }
        }
    }

    for (int i = 0; i < colors.size(); i++) {
        if (colors[i].objRef == objRef) {
            if (state == GLUT_DOWN) {
                colors[i].isClicked = true;
                glutPostRedisplay();
                return;
            } else {
                colors[i].isClicked = false;
                colors[i].swatchCallBack();
                glutPostRedisplay();
                return;
            }
        }
    }
}

void Toolbar::initColors()
{
    //create the collor swatch area
    cout << "Would set up colors\n";
    SwatchButton b(20, 270, 20, 20, &Callbacks::changeLineColorCallBack, &callbacks, this->objRef++, Color(1.0f, 0.0f, 0.0f));
    colors.push_back(b);
    b = SwatchButton(50, 270, 20, 20, &Callbacks::changeLineColorCallBack, &callbacks, this->objRef++, Color(0.0f, 1.0f, 0.0f));
    colors.push_back(b);
    b = SwatchButton(80, 270, 20, 20, &Callbacks::changeLineColorCallBack, &callbacks, this->objRef++, Color(0.0f, 0.0f, 1.0f));
    colors.push_back(b);
    b = SwatchButton(20, 240, 20, 20, &Callbacks::changeLineColorCallBack, &callbacks, this->objRef++, Color(0.0f, 0.0f, 0.0f));
    colors.push_back(b);
    b = SwatchButton(50, 240, 20, 20, &Callbacks::changeLineColorCallBack, &callbacks, this->objRef++, Color(0.5f, 0.5f, 0.5f));
    colors.push_back(b);
    b = SwatchButton(80, 240, 20, 20, &Callbacks::changeLineColorCallBack, &callbacks, this->objRef++, Color(1.0f, 1.0f, 1.0f));
    colors.push_back(b);
}
