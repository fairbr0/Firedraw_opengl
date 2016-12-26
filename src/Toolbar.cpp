#include "Toolbar.h"
#include "Button.h"
#include <vector>
#include <iostream>
#include <GLUT/glut.h>
#include "Callbacks.h"
#include "StickyButton.h"
#include "SwatchButton.h"
#include "Context.h"
#include <string>
#include "Element.h"

using namespace std;

Toolbar::Toolbar(Context *c, int height, int width)
{
    this->c = c;
    this->top = height;
    this->right = width;
    this->callbacks = Callbacks(c);
    this->objRef = 1000000;
    this->sqrBtn = Button(right / 2, top - 30, 80, 40, "Square", &Callbacks::squareSelectedCallBack, &callbacks, this->objRef++);
    this->crlBtn = Button(right / 2, top - 80, 80, 40, "Circle", &Callbacks::circleSelectedCallBack, &callbacks, this->objRef++);
    this->triBtn = Button(right / 2, top - 130, 80, 40, "Triangle", &Callbacks::triangleSelectedCallBack, &callbacks, this->objRef++);
    this->txtBtn = Button(right / 2, top - 180, 80, 40, "Text", &Callbacks::triangleSelectedCallBack, &callbacks, this->objRef++);
    this->lneBtn = Button(right / 2, top - 230, 80, 40, "Line", &Callbacks::triangleSelectedCallBack, &callbacks, this->objRef++);
    this->dlwBtn = Button(right / 4, top - 280, 40, 40, "-", &Callbacks::decreaseLineWeightCallBack, &callbacks, this->objRef++);
    this->ilwBtn = Button(3 * right / 4, top - 280, 40, 40, "+", &Callbacks::increaseLineWeightCallBack, &callbacks, this->objRef++);
    this->fillBtn = StickyButton(right / 2, top - 330, 80, 40, "Filled", &Callbacks::toggleFilledCallBack, &callbacks, this->objRef++);
    this->lcBtn = StickyButton(right / 4, top - 380, 40, 40, "Line", &Callbacks::changeLineColorCallBack, &callbacks, this->objRef++);
    this->fcBtn = StickyButton(right / 4, top - 430, 40, 40, "Fill", &Callbacks::changeFillColorCallBack, &callbacks, this->objRef++);
    this->lcBox = Square(Point(3 * right /4, 380), 40, 40, this->objRef++, Element(true, 1.0, Color(0, 0, 0), *c->getLineColor()), "SQUARE");
    this->fcBox = Square(Point(3 * right /4, 430), 40, 40, this->objRef++, Element(true, 1.0, Color(0, 0, 0), *c->getFillColor()), "SQUARE");
    cout << "make first set\n";
    buttons.push_back(&sqrBtn);
    buttons.push_back(&triBtn);
    buttons.push_back(&crlBtn);
    buttons.push_back(&txtBtn);
    buttons.push_back(&lneBtn);
    buttons.push_back(&ilwBtn);
    buttons.push_back(&dlwBtn);
    stickyButtons.push_back(&fillBtn);
    stickyButtons.push_back(&lcBtn);
    stickyButtons.push_back(&fcBtn);

    int offset = top - 600;

    cout << "about to create trans buttons\n";
    this->dtBtn = Button(right / 4, offset - 30, 40, 40, "-", &Callbacks::decreaseTransparencyCallBack, &callbacks, this->objRef++);
    this->itBtn = Button(3 * right / 4, offset - 30, 40, 40, "+", &Callbacks::increaseTransparencyCallBack, &callbacks, this->objRef++);
    this->clrBtn = Button(right / 2, offset - 80, 80, 40, "Clear", &Callbacks::clearCanvasCallBack, &callbacks, this->objRef++);
    this->mveBtn = StickyButton(right / 4, offset - 130, 40, 40, "Move", &Callbacks::selectMoveToolCallBack, &callbacks, this->objRef++);
    this->drwBtn = StickyButton(3 * right / 4, offset - 130, 40, 40, "Draw", &Callbacks::selectDrawToolCallBack, &callbacks, this->objRef++);
    this->delBtn = Button(right / 4, offset - 180, 40, 40, "Delete", &Callbacks::deleteSelectedCallBack, &callbacks, this->objRef++);
    buttons.push_back(&dtBtn);
    buttons.push_back(&itBtn);
    buttons.push_back(&clrBtn);
    stickyButtons.push_back(&mveBtn);
    stickyButtons.push_back(&drwBtn);
    buttons.push_back(&delBtn);
    this->sveBtn = Button(right / 2, 30, 80, 40, "Save", &Callbacks::saveCallBack, &callbacks, this->objRef++);
    this->opnBtn = Button(right / 2, 80, 80, 40, "Open", &Callbacks::loadCallBack, &callbacks, this->objRef++);
    buttons.push_back(&sveBtn);
    buttons.push_back(&opnBtn);
    offset = this->initColors(top - 450);
    this->lcBtn.toggleEnabled();
    this->drwBtn.toggleEnabled();
}

void Toolbar::setDrawMode()
{
    mveBtn.setEnabled(false);
    drwBtn.setEnabled(true);
}

void Toolbar::setMoveMode()
{
    mveBtn.setEnabled(true);
    drwBtn.setEnabled(false);
}

void Toolbar::draw()
{

    glColor3f(0.8, 0.8, 0.8);
    glPushName(999999);
    glBegin(GL_POLYGON);
        glVertex2f(0, 0);
        glVertex2f(0, 1000);
        glVertex2f(100, 1000);
        glVertex2f(100, 0);
    glEnd();

    for (int i = 0; i < buttons.size(); i++) {
        if (buttons[i]) {
            (buttons[i])->drawButton();
        }
    }

    for (size_t i = 0; i < stickyButtons.size(); i++) {
        if (stickyButtons[i])
            (stickyButtons[i])->drawButton();
    }
    for (int i = 0; i < colors.size(); i++) {
        colors[i].drawButton();
    }

    this->lcBox.elem.setFillColor(*c->getLineColor());
    this->fcBox.elem.setFillColor(*c->getFillColor());
    this->lcBox.drawShape();
    this->fcBox.drawShape();
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

    for (int i = 0; i < stickyButtons.size(); i++) {
        if ((stickyButtons[i])->objRef == objRef) {
            if (state == GLUT_DOWN) {
                (stickyButtons[i])->isClicked = true;
                glutPostRedisplay();
                return;
            } else {
                (stickyButtons[i])->isClicked = false;
                if (stickyButtons[i]->whoami() == "Filled") fillBtn.toggleEnabled();
                if (stickyButtons[i]->whoami() == "Line" || stickyButtons[i]->whoami() == "Fill") {
                    if (!stickyButtons[i]->isEnabled()){
                        lcBtn.toggleEnabled();
                        fcBtn.toggleEnabled();
                    }
                }
                if (stickyButtons[i]->whoami() == "Move" || stickyButtons[i]->whoami() == "Draw") {
                    if (!stickyButtons[i]->isEnabled()){
                        mveBtn.toggleEnabled();
                        drwBtn.toggleEnabled();
                    }
                }
                (stickyButtons[i])->callBack();
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



void Toolbar::deselectAll()
{
    for (int i = 0; i < buttons.size(); i++) {
        buttons[i]->isClicked = false;
    }
    for (int i = 0; i < stickyButtons.size(); i++) {
        stickyButtons[i]->isClicked = false;
    }
    for (int i = 0; i < colors.size(); i++) {
        colors[i].isClicked = false;
    }
}

int Toolbar::initColors(int offset)
{
    //create the collor swatch area
    cout << "Would set up colors\n";
    SwatchButton b(right - 80, offset - 20, 20, 20, &Callbacks::changeColorCallBack, &callbacks, this->objRef++, Color(1.0f, 0.0f, 0.0f));
    colors.push_back(b);
    b = SwatchButton(right - 50, offset - 20, 20, 20, &Callbacks::changeColorCallBack, &callbacks, this->objRef++, Color(0.0f, 1.0f, 0.0f));
    colors.push_back(b);
    b = SwatchButton(right - 20, offset - 20, 20, 20, &Callbacks::changeColorCallBack, &callbacks, this->objRef++, Color(0.0f, 0.0f, 1.0f));
    colors.push_back(b);
    b = SwatchButton(right - 80, offset - 50, 20, 20, &Callbacks::changeColorCallBack, &callbacks, this->objRef++, Color(0.0f, 0.0f, 0.0f));
    colors.push_back(b);
    b = SwatchButton(right - 50, offset - 50, 20, 20, &Callbacks::changeColorCallBack, &callbacks, this->objRef++, Color(0.5f, 0.5f, 0.5f));
    colors.push_back(b);
    b = SwatchButton(right - 20, offset - 50, 20, 20, &Callbacks::changeColorCallBack, &callbacks, this->objRef++, Color(1.0f, 1.0f, 1.0f));
    colors.push_back(b);

    return offset - 70;
}
