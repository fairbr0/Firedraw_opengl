#include "Popover.h"
#include <GLUT/glut.h>
#include "Callbacks.h"
#include "Context.h"
#include <iostream>

using namespace std;

Popover::Popover()
{

}

Popover::Popover(Callbacks* c, void (Callbacks::*callBack_func)(string), void (Callbacks::*cancelFunc)(), string buttonLabel, string windowTitle, string windowDescription)
{
    this->buttonLabel = buttonLabel;
    this->windowTitle = windowTitle;
    this->windowDescription = windowDescription;
    //cout << "popover callback context @" << callbacks.c << "\n";
    this->cancelBtn = Button(-120.0, -60.0, 80.0, 40.0, "Cancel", cancelFunc, c, 2000000);
    this->nextBtn = PopoverButton(120.0, -60.0, 80.0, 40.0, buttonLabel, callBack_func, c, 2000001);
    //cout << "Finished creating popover. Callbacks ref = " << &callbacks << " Context ref = " << c << "\n";
}

void Popover::handleClickEvent(int objRef, int state) {
    cout << "in popover callback \n";
    if (objRef == 2000000) {
        cancelBtn.callBack();
    } else {
        nextBtn.callBack("hello");
    }
}

void Popover::display()
{
    glPushMatrix();
        glTranslatef(500, 500, 0);
        glColor3f(0.8, 0.8, 0.8);
        glBegin(GL_POLYGON);
            glVertex2f(-175, 100);
            glVertex2f(175, 100);
            glVertex2f(175, -100);
            glVertex2f(-175, -100);
        glEnd();

    cancelBtn.drawButton();
    nextBtn.drawButton();
    glPopMatrix();
}
