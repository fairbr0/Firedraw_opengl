#include "Shape.h"
#include <GLUT/glut.h>
#include <vector>
#include <iostream>

Shape::Shape()
{
    center = Point(0.0f, 0.0f);
    rotation = 0.0;
}

Shape::Shape(Point p, int w, int h, int objRef, Element e)
{
    center = p;
    width = w;
    height = h;
    rotation = 0.0;
    this->objRef = objRef;
    elem = e;
}

Shape::Shape(Point p, int w, int h, int objRef)
{
    center = p;
    width = w;
    height = h;
    rotation = 0.0;
    this->objRef = objRef;
    elem = Element();
}

Point Shape::getCenter()
{
    return center;
}

double Shape::getRotation()
{
    return rotation;
}

void Shape::move(float x, float y) {
    float org_x = center.getPoint()[0];
    float org_y = center.getPoint()[1];
    center.move(org_x + x, org_y + y);
}

void Shape::setCenter(Point p) {
    this->center = p;
}

void Shape::setRotation(double r)
{
    rotation = r;
}

void Shape::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
}

int Shape::getHeight()
{
    return this->height;
}

int Shape::getWidth()
{
    return this->width;
}

int Shape::getObjRef()
{
    return this->objRef;
}

void Shape::drawShape()
{
    vector<float> colors = this->elem.getLineColor().getColors();
    glColor4f(colors[0], colors[1], colors[2], colors[3]);
    glLineWidth(this->elem.getLineWeight());
    glPushMatrix();
        glTranslatef(center.getPoint()[0], 1000-center.getPoint()[1], 0.0f);
        glScalef((GLfloat) width, (GLfloat) height, 1.0f);
        glLoadName(this->objRef);
        glBegin(GL_LINE_LOOP);
            for (std::vector<int>::size_type i = 0; i < geometry.size(); i++) {
                glVertex2fv(geometry[i].getPoint());
                }
        glEnd();
        if (elem.getIsFilled()) {
            vector<float> colors = this->elem.getFillColor().getColors();
            glColor4f(colors[0], colors[1], colors[2], colors[3]);
            glBegin(GL_POLYGON);
                for (std::vector<int>::size_type i = 0; i < geometry.size(); i++) {
                    glVertex2fv(geometry[i].getPoint());
                    }
            glEnd();
        }
    glPopMatrix();
}
