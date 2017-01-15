#include "Popover.h"
#include "Callbacks.h"
#include "Context.h"
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

//Popover class. Creates a box over the top of drawn content, with a message and text entry area.

Popover::Popover()
{

}

//popover given a context, callback function for an action and to cancel, a label, message and button label.
Popover::Popover(Context* cont, Callbacks* c, void (Callbacks::*callBack_func)(string), void (Callbacks::*cancelFunc)(), string buttonLabel, string windowTitle, string windowDescription)
{
    this->buttonLabel = buttonLabel;
    this->windowTitle = windowTitle;
    this->windowDescription = windowDescription;
    this->context = cont;
    this->cancelBtn = Button(-120.0, -60.0, 80.0, 40.0, "Cancel", cancelFunc, c, 2000002);
    this->nextBtn = PopoverButton(120.0, -60.0, 80.0, 40.0, buttonLabel, callBack_func, c, 2000003);
}

//handle clicks on the box.
void Popover::handleClickEvent(int objRef, int state) {
    switch (objRef) {
        case 2000000:
        case 2000001:
            // blank area clicked, cancel all button clicks
            deselectAll();
            glutPostRedisplay();
            break;
        case 2000002:
            //cancle button clicked.
            if (state == GLUT_DOWN) {
                cancelBtn.isClicked = true;
            } else {
                cancelBtn.isClicked = false;
                cancelBtn.callBack();
            }
            glutPostRedisplay();
            break;
        case 2000003:
            //action button clicked
            if (state == GLUT_DOWN) {
                nextBtn.isClicked = true;
            } else {
                nextBtn.isClicked = false;
                nextBtn.callBack(inputText);
            }
            glutPostRedisplay();
            break;
        case 2000004:
            //text entry area clicked
            if (state == GLUT_DOWN) {
                textAreaSelected = true;
            } else {
                textAreaSelected = true;
                context->setKeyboardCaptured(true);
                //set to capture keyboard input from shortcuts
            }
            glutPostRedisplay();
            break;
    }
}

//add typed char to user input string
void Popover::addChar(unsigned char c)
{
    //detect the delete char
    if (c == 127 || c == 8) {
        //check string not empty before deletion
        if (this->inputText.size() > 0) {
            this->inputText.resize(this->inputText.size() - 1);
        }
    } else {
        this->inputText += c;
    }
    glutPostRedisplay();
}

//unselect all buttons
void Popover::deselectAll()
{
    this->cancelBtn.isClicked = false;
    this->nextBtn.isClicked = false;
    this->textAreaSelected = false;
    context->setKeyboardCaptured(false);
}

//display the popover.
void Popover::display()
{
    glColor4f(0.9, 0.9, 0.9, 0.4);
    glLoadName(2000000);
    //grey out the screen behind the popover
    glBegin(GL_POLYGON);
        glVertex2f(0, 1000);
        glVertex2f(1000, 1000);
        glVertex2f(1000, 0);
        glVertex2f(0, 0);
    glEnd();
    glPushMatrix();
        //draw the popover box
        glTranslatef(500, 500, 0);
        glColor3f(0.8, 0.8, 0.8);
        glLoadName(2000001);
        glBegin(GL_POLYGON);
            glVertex2f(-175, 100);
            glVertex2f(175, 100);
            glVertex2f(175, -100);
            glVertex2f(-175, -100);
        glEnd();
        //draw the grey title bar
        glColor3f(0.9, 0.9, 0.9);
        glBegin(GL_POLYGON);
            glVertex2f(-175, 100);
            glVertex2f(175, 100);
            glVertex2f(175, 70);
            glVertex2f(-175, 70);
        glEnd();

        //add the popover title
        glPushMatrix();
            glTranslatef(0, 78, 0);
            glScalef(0.15, 0.15, 1);
            drawText(windowTitle);
        glPopMatrix();

        //add the popover description
        glPushMatrix();
            glTranslatef(0, 40, 0);
            glScalef(0.1, 0.1, 1);
            drawText(windowDescription);
        glPopMatrix();

        //add the text entry boc
        glColor3f(1, 1, 1);
        glLoadName(2000004);
        glBegin(GL_POLYGON);
            glVertex2f(-100, 20);
            glVertex2f(100, 20);
            glVertex2f(100, -20);
            glVertex2f(-100, -20);
        glEnd();

        //display current user input in the text box.
        glPushMatrix();
            glScalef(0.1, 0.1, 1);
            drawText(inputText);
        glPopMatrix();
        //highlight the text area if its selected
        if (textAreaSelected) {
            glColor3f(0.1, 0.1, 0.1);
            glBegin(GL_LINE_LOOP);
                glVertex2f(-100, 20);
                glVertex2f(100, 20);
                glVertex2f(100, -20);
                glVertex2f(-100, -20);
            glEnd();
        }

        //add the cancel and action buttons
        cancelBtn.drawButton();
        nextBtn.drawButton();

    glPopMatrix();
}

//method to draw text. Computes the string length (pixels), centralises and then draws the characters
void Popover::drawText(string s)
{
    int width = 0;
    for (int i = 0; i < s.size(); i++)
        width += glutStrokeWidth(GLUT_STROKE_ROMAN, s[i]);

    glTranslatef(-width / 2, 0.0, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    for (int i = 0; i < s.size(); i++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i]);
    }
}
