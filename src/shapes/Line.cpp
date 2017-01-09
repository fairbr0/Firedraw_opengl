#include "Line.h"
#ifdef __APPLE__
#include <GLUT/glut.h> 
#else
#include <GL/glut.h> 
#endif

Line::Line()
{

}

void Line::drawShape()
{
    vector<float> colors = this->elem.getLineColor().getColors();
    std::cout << "alpha channel LINE: " << colors[3] << "\n";
    glColor4f(colors[0], colors[1], colors[2], colors[3]);
    glLineWidth(this->elem.getLineWeight());
    glPushMatrix();
        cout << "drawing line\n";
        glLoadName(this->objRef);
        glBegin(GL_LINES);
            for (std::vector<int>::size_type i = 0; i < geometry.size(); i++) {
                glVertex2fv(geometry[i].getPoint());
                }
        glEnd();

    glPopMatrix();
}

void Line::rotate()
{

}

void Line::move(float x, float y)
{
    float org_x = center.getPoint()[0];
    float org_y = center.getPoint()[1];
    center.move(org_x + x, org_y + y);
    org_x = end.getPoint()[0];
    org_y = end.getPoint()[1];
    end.move(org_x + x, org_y + y);
}

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

Point Line::getP1()
{
    return center;
}

Point Line::getP2()
{
    return end;
}
