#include "Line.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

Line::Line()
{

}

/* overridden method to draw a line. The line endpoints are drawn directly,
instead of being a generic line shape, then being translated, rotated etc as
other shapes are. */
void Line::drawShape()
{
    vector<float> colors = this->elem.getLineColor().getColors();
    glColor4f(colors[0], colors[1], colors[2], colors[3]);
    glLineWidth(this->elem.getLineWeight());
    glPushMatrix();
        glLoadName(this->objRef);
        glBegin(GL_LINES);
            glVertex2fv(center.getPoint());
            glVertex2fv(end.getPoint());
        glEnd();

    glPopMatrix();
}

void Line::rotate()
{

}

//Method to move a lines position on screen.
void Line::move(float x, float y)
{
    float org_x = center.getPoint()[0];
    float org_y = center.getPoint()[1];
    center.move(org_x + x, org_y + y);
    org_x = end.getPoint()[0];
    org_y = end.getPoint()[1];
    end.move(org_x + x, org_y + y);
}


//Method to move an endpoint of the line
void Line::movePoint(float x, float y, bool p)
{
    Point* f;
    if (p) {
        f = &center;
    } else {
        f = &end;
    }
    float org_x = f->getPoint()[0];
    float org_y = f->getPoint()[1];
    f->move(org_x + x, org_y + y);
}

//methods to return endpoints. P1 is the initial click location, P2 the final one
Point Line::getP1()
{
    return center;
}

Point Line::getP2()
{
    return end;
}
