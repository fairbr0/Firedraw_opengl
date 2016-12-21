#include "Context.h"
#include "Square.h"
#include "Triangle.h"
#include "Circle.h"
#include <vector>
#include <iostream>


Context::Context()
{
    appIsClicked = false;
    appShapeToDraw = SQUARE;
    appNextObjectId = 0;
    appRenderMode = GL_RENDER;
    appFillShape = false;
    appFillColor = Color(0.0f, 0.0f, 0.0f);
    appLineColor = Color(0.0f, 0.0f, 0.0f);
    appLineWeight = 2.0f;
}

/************ SETTERS **********/

void Context::setShapeToDraw(int id)
{
    this->appShapeToDraw = id;
}

void Context::setToolMode(int tool)
{
    this->appToolMode = tool;
}

void Context::setMouseX(float x)
{
    this->mouse_x = x;
}

void Context::setMouseY(float y)
{
    this->mouse_y = y;
}

void Context::setPrevMouseX(float x)
{
    this->mouse_prev_x = x;
}

void Context::setPrevMouseY(float y)
{
    this->mouse_prev_y = y;
}

void Context::setRenderMode(int renderMode)
{
    this->appRenderMode = renderMode;
}

void Context::setInitialDrawPoint(Point p)
{
    this->drawInitialPoint = p;
}

void Context::isClicked(bool clicked)
{
    this->appIsClicked = clicked;
}

void Context::setObjectId(int id){
    this->appNextObjectId = id;
}

void Context::setSelectedObject(int id)
{
    if (appClickedObject) {
        appPrevClickedObject = appClickedObject;
    }
    appClickedObject = 0;
    std::cout << "id: " << id << "\n";
    for (int i = 0; i < appShapes.size(); i++) {
        if (appShapes[i].getObjRef() == id) {
            appClickedObject = &appShapes[i];
        }
    }
}

void Context::setPrevSelectedObject(Shape *s){
    this->appPrevClickedObject = s;
}

void Context::setFillColor(Color c)
{
    this->appFillColor = c;
}

void Context::setLineColor(Color c)
{
    this->appLineColor = c;
}

void Context::setLineWeight(float w)
{
    this->appLineWeight = w;
}

void Context::setIsFilled(bool b)
{
    this->appFillShape = b;
}

/********* GETTERS *********/

unsigned int* Context::getPickBuffer()
{
    return PickBuffer;
}

bool Context::isClicked()
{
    return this->appIsClicked;
}

int Context::getRenderMode()
{
    return this->appRenderMode;
}

float Context::getMouseX()
{
    return this->mouse_x;
}

float Context::getMouseY()
{
    return this->mouse_y;
}

float Context::getPrevMouseX()
{
    return this->mouse_prev_x;
}

float Context::getPrevMouseY()
{
    return this->mouse_prev_y;
}

int Context::getToolMode()
{
    return this->appToolMode;
}

int Context::getShapeToDraw()
{
    return this->appShapeToDraw;
}

int Context::getObjectId()
{
    return this->appNextObjectId;
}

float Context::getLineWeight()
{
    return this->appLineWeight;
}

bool Context::getIsFilled()
{
    return this->appFillShape;
}

Color* Context::getLineColor()
{
    return &appLineColor;
}

Color* Context::getFillColor()
{
    return &appFillColor;
}

Shape* Context::getSelectedObject()
{
    return appClickedObject;
}

Shape* Context::getPrevSelectedObject()
{
    return appPrevClickedObject;
}

Point* Context::getInitialDrawPoint()
{
    return &drawInitialPoint;
}

std::vector<Shape> * Context::getShapes()
{
    return &appShapes;
}

std::vector<Shape> * Context::getTempShapes()
{
    return &tempShapes;
}

/************ METHODS **********/

Shape Context::newShape(Point mid, int x, int y, int ref)
{
    Shape s;
    Element e = Element(appFillShape, appLineWeight, appLineColor, appFillColor);
    switch (appShapeToDraw) {
        case SQUARE: s = Square(mid, x, y, ref, e); break;
        case TRIANGLE: s = Triangle(mid, x, y, ref, e); break;
        case CIRCLE: s = Circle(mid, x, y, ref, e); break;
    }
    return s;
}

void Context::createEditBox()
{
    Shape o = *this->appClickedObject;
    Shape s = Square(o.getCenter(), o.getWidth(), o.getHeight(), -1, o.elem);
    s.elem.setIsFilled(false);
    s.elem.setLineWeight(1.0f);
    s.elem.setLineColor(Color(0.4, 0.4, 0.4, 0.7));
    this->tempShapes.push_back(s);

    Element e = Element(true, 1.0f, Color(1.0, 0.0, 0.0, 0.7), Color(1.0, 0.0, 0.0, 0.7));

    Point p = o.getCenter();
    p.move(p.getPoint()[0] - o.getWidth()/2, p.getPoint()[1] - o.getHeight()/2);
    Shape c0 = Square(p, 5, 5, -2, e);
    this->tempShapes.push_back(c0);

    p = o.getCenter();
    p.move(p.getPoint()[0] + o.getWidth()/2, p.getPoint()[1] - o.getHeight()/2);
    Shape c1 = Square(p, 5, 5, -3, e);
    this->tempShapes.push_back(c1);

    p = o.getCenter();
    p.move(p.getPoint()[0] + o.getWidth()/2, p.getPoint()[1] + o.getHeight()/2);
    Shape c2 = Square(p, 5, 5, -4, e);
    this->tempShapes.push_back(c2);

    p = o.getCenter();
    p.move(p.getPoint()[0] - o.getWidth()/2, p.getPoint()[1] + o.getHeight()/2);
    Shape c3 = Square(p, 5, 5, -5, e);
    this->tempShapes.push_back(c3);

    e.setFillColor(Color(0.0, 1.0, 0.0));
    e.setLineColor(Color(0.0, 1.0, 0.0));
    p = o.getCenter();
    p.move(p.getPoint()[0], p.getPoint()[1] + o.getHeight()/2);
    Shape c4 = Square(p, 5, 5, -6, e);
    this->tempShapes.push_back(c4);
}

void Context::resetAppShapes()
{
    appShapes = std::vector<Shape>();
}

void Context::resetTempShapes()
{
    tempShapes = std::vector<Shape>();
}
