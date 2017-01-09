#include "StickyButton.h"
#include <vector>
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h> 
#else
#include <GL/glut.h> 
#endif

StickyButton::StickyButton(){

}

void StickyButton::callBack()
{
    Button::callBack();
}

void StickyButton::drawButton()
{
    float color[4];
    glPushMatrix();
        glTranslatef(this->x, this->y, 0.0f);
        glPushMatrix();
            glScalef(this->w, this->h, 0.0f);
            glLoadName(this->objRef);
            if (isClicked || isEnabled()) {
                glColor3f(0.65, 0.65, 0.65);
            } else {
                glColor3f(0.7, 0.7, 0.7);
            }
            glBegin(GL_POLYGON);
            for (int i = 0; i < 4; i++) {
                float vec[2];
                vec[0] = geometry[i].getPoint()[0];
                vec[1] = geometry[i].getPoint()[1];

                glVertex2fv(vec);
            }
            glEnd();
            if (this->isClicked || this->enabled) {
                glGetFloatv(GL_CURRENT_COLOR, color);
                glColor3f(0.0f, 0.0f, 0.0f);
                glBegin(GL_LINE_LOOP);
                for (int i = 0; i < 4; i++) {
                    float vec[2];
                    vec[0] = geometry[i].getPoint()[0];
                    vec[1] = geometry[i].getPoint()[1];

                    glVertex2fv(vec);
                }
                glEnd();
                glColor3f(color[0], color[1], color[2]);
            }
        glPopMatrix();

        glGetFloatv(GL_CURRENT_COLOR, color);
        glPushMatrix();

            glTranslatef(0.0f, 0.0f, 0.0f);
            glScalef(0.1, 0.1, 0.0);

            int width = 0;
            for (int i = 0; i < this->label.size(); i++)
                width += glutStrokeWidth(GLUT_STROKE_ROMAN, this->label[i]);

            glTranslatef(-width / 2, 0.0, 0.0f);
            glColor3f(0.0f, 0.0f, 0.0f);
            glLineWidth(1.0f);
            for (int i = 0; i < this->label.size(); i++) {
                glutStrokeCharacter(GLUT_STROKE_ROMAN, this->label[i]);
            }
        glPopMatrix();
        glColor3f(color[0], color[1], color[2]);
    glPopMatrix();
}

void StickyButton::toggleEnabled()
{
    this->enabled = !this->enabled;
}

void StickyButton::setEnabled(bool b)
{
    this->enabled = b;
}

bool StickyButton::isEnabled()
{
    return this->enabled;
}
