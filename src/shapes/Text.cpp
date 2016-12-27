#include "Text.h"
#include <GLUT/glut.h>
#include <iostream>
#include <string>

Text::Text()
{

}

void Text::drawShape()
{
    vector<float> colors = this->elem.getLineColor().getColors();
    std::cout << "alpha channel LINE: " << colors[3] << "\n";
    glColor4f(colors[0], colors[1], colors[2], colors[3]);
    glLineWidth(this->elem.getLineWeight());
    glPushMatrix();
        glTranslatef(center.getPoint()[0], 1000-center.getPoint()[1], 0.0f);
        glRotatef(rotation, 0, 0, 1);
        glScalef((GLfloat) width * 0.01, (GLfloat) height * 0.01, 1.0f);

        glLoadName(this->objRef);
        drawText(this->text);

    glPopMatrix();
}

void Text::drawText(string s)
{
    int width = 0;
    for (int i = 0; i < s.size(); i++)
        width += glutStrokeWidth(GLUT_STROKE_ROMAN, s[i]);

    glTranslatef(-width / 2, -50, 0.0f);
    vector<float> colors = this->elem.getLineColor().getColors();
    std::cout << "alpha channel LINE: " << colors[3] << "\n";
    glColor4f(colors[0], colors[1], colors[2], colors[3]);
    glLineWidth(this->elem.getLineWeight());
    for (int i = 0; i < s.size(); i++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i]);
    }
}
