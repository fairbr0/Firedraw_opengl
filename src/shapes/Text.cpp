#include "Text.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <string>

Text::Text()
{

}

//method overriden to draw text to the screen.
void Text::drawShape()
{
    vector<float> colors = this->elem.getLineColor().getColors();
    glColor4f(colors[0], colors[1], colors[2], colors[3]);
    glLineWidth(this->elem.getLineWeight());
    glPushMatrix();
    // position the text to be drawn
        glTranslatef(center.getPoint()[0], center.getPoint()[1], 0.0f);
        glRotatef(rotation, 0, 0, 1);
        glScalef((GLfloat) width * 0.01, (GLfloat) height * 0.01, 1.0f);

        glLoadName(this->objRef);
        //draw the characters
        drawText(this->text);

    glPopMatrix();
}

//method to draw characters
void Text::drawText(string s)
{
    //compute the width of the string
    int width = 0;
    for (int i = 0; i < s.size(); i++)
        width += glutStrokeWidth(GLUT_STROKE_ROMAN, s[i]);
    // translate text by half the string width, so it is drawn central in its bounding box
    glTranslatef(-width / 2, -50, 0.0f);
    vector<float> colors = this->elem.getLineColor().getColors();
    glColor4f(colors[0], colors[1], colors[2], colors[3]);
    glLineWidth(this->elem.getLineWeight());
    //draw the characters to screen
    for (int i = 0; i < s.size(); i++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i]);
    }
}

string Text::getLabel()
{
  return this->text;
}
