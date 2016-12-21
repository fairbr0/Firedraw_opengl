#include "SwatchButton.h"
#include "Color.h"
#include <vector>
#include <iostream>
#include <GLUT/glut.h>

using namespace std;

SwatchButton::SwatchButton()
{

}

void SwatchButton::drawButton()
{
    glPushMatrix();
        float oldColors[4];
        glGetFloatv(GL_CURRENT_COLOR, oldColors);
        glTranslatef(this->x, this->y, 0.0f);
        glPushMatrix();
            glScalef(this->w, this->h, 0.0f);
            vector<float> color = this->color.getColors();
            glColor3f(color[0], color[1], color[2]);
            glLoadName(this->objRef);
            glBegin(GL_POLYGON);
            for (int i = 0; i < 4; i++) {
                float vec[2];
                vec[0] = geometry[i].getPoint()[0];
                vec[1] = geometry[i].getPoint()[1];

                glVertex2fv(vec);
            }
            glEnd();
        glPopMatrix();
        glColor3f(oldColors[0], oldColors[1], oldColors[2]);
    glPopMatrix();
}

Color SwatchButton::getColor()
{
    return this->color;
}

void SwatchButton::swatchCallBack()
{
    (callbacks->*swatchCallBack_func)(color);
}
