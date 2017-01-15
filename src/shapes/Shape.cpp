#include "Shape.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <vector>
#include <iostream>
#include <string>

//Base shape class. Shape has a center, width and height for basic drawing.
Shape::Shape()
{
    center = Point(0.0f, 0.0f);
    rotation = 0.0;
}

Shape::Shape(Point p, int w, int h, int objRef, Element e, string type)
{
    center = p;
    width = w;
    height = h;
    rotation = 0.0;
    this->objRef = objRef;
    elem = e;
    this->type = type;
}

Shape::Shape(Point p, int w, int h, int objRef, string type)
{
    center = p;
    width = w;
    height = h;
    rotation = 0.0;
    this->objRef = objRef;
    elem = Element();
    this->type = type;
}

Point Shape::getCenter()
{
    return center;
}

float Shape::getRotation()
{
    return rotation;
}

string Shape::getType()
{
    return this->type;
}

//move the shape to the given location
void Shape::move(float x, float y) {
    float org_x = center.getPoint()[0];
    float org_y = center.getPoint()[1];
    center.move(org_x + x, org_y + y);
}

void Shape::setCenter(Point p) {
    this->center = p;
}

void Shape::setEnd(Point p) {
    this->end = p;
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
        glTranslatef(center.getPoint()[0], center.getPoint()[1], 0.0f);
        glRotatef(rotation, 0, 0, 1);
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

string Shape::toString()
{
    return "";
}
