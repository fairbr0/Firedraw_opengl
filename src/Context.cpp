#include "Context.h"
#include "Square.h"
#include "Triangle.h"
#include "Circle.h"
#include <vector>
#include <iostream>
#include <string>


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

void Context::setColor(Color c)
{
    if (colorToChange) {
        setLineColor(c);
    } else {
        setFillColor(c);
    }
}

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
    if (appClickedObject) {
        appClickedObject->elem.setFillColor(c);
        glutPostRedisplay();
    }
}

void Context::setLineColor(Color c)
{
    this->appLineColor = c;
    if (appClickedObject) {
        appClickedObject->elem.setLineColor(c);
        glutPostRedisplay();
    }
}

void Context::setLineWeight(float w)
{
    this->appLineWeight = w;
    if (appClickedObject) {
        appClickedObject->elem.setLineWeight(w);
        glutPostRedisplay();
    }
}

void Context::setIsFilled(bool b)
{
    this->appFillShape = b;
    if (appClickedObject) {
        appClickedObject->elem.setIsFilled(b);
        glutPostRedisplay();
    }
}

void Context::increaseAlpha()
{

    if (appClickedObject) {
        if (colorToChange) {
            // change line alpha
            float alpha = appClickedObject->elem.lineColor.getColors()[3] + 0.05;
            if (alpha > 1) alpha = 1;
            appClickedObject->elem.lineColor.setAlpha(alpha);
        } else {
            // change fill alpha
            float alpha = appClickedObject->elem.fillColor.getColors()[3] + 0.05;
            if (alpha > 1) alpha = 1;
            appClickedObject->elem.fillColor.setAlpha(alpha);
        }
        glutPostRedisplay();
    } else {
        if (colorToChange) {
            // change line alpha
            float alpha = appLineColor.getColors()[3] + 0.05;
            if (alpha > 1) alpha = 1;
            appLineColor.setAlpha(alpha);
        } else {
            // change fill alpha
            float alpha = appFillColor.getColors()[3] + 0.05;
            if (alpha > 1) alpha = 1;
            appFillColor.setAlpha(alpha);
        }
    }
}

void Context::decreaseAlpha() {
    if (appClickedObject) {
        if (colorToChange) {
            // change line alpha
            float alpha = appClickedObject->elem.lineColor.getColors()[3] - 0.05;
            if (alpha < 0) alpha = 0;
            appClickedObject->elem.lineColor.setAlpha(alpha);
        } else {
            // change fill alpha
            float alpha = appClickedObject->elem.fillColor.getColors()[3] - 0.05;
            if (alpha < 0) alpha = 0;
            appClickedObject->elem.fillColor.setAlpha(alpha);
        }
        glutPostRedisplay();
    } else {
        if (colorToChange) {
            // change line alpha
            float alpha = appLineColor.getColors()[3] - 0.05;
            if (alpha < 0) alpha = 0;
            appLineColor.setAlpha(alpha);
        } else {
            // change fill alpha
            float alpha = appFillColor.getColors()[3] - 0.05;
            if (alpha < 0) alpha = 0;
            appFillColor.setAlpha(alpha);
        }
    }

}

void Context::setShapes(vector<Shape> shapes)
{
    this->appShapes = shapes;
}

void Context::setCreatePopup(int type)
{
    this->createPopup = true;
    this->newPopupType = type;
    glutPostRedisplay();
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

bool Context::checkShoulCreatePopup() {
    return createPopup;
}

int Context::getNewPopoverType()
{
    std::cout << "should createPopup : " << createPopup << "\n";
    if (!createPopup) return -1;
    else {
        createPopup = false;
        return newPopupType;
    }
}

/************ METHODS **********/

Shape Context::newShape(Point mid, int x, int y, int ref)
{
    Shape s;
    Element e = Element(appFillShape, appLineWeight, appLineColor, appFillColor);
    switch (appShapeToDraw) {
        case SQUARE: s = Square(mid, x, y, ref, e, "SQUARE"); break;
        case TRIANGLE: s = Triangle(mid, x, y, ref, e, "TRIANGLE"); break;
        case CIRCLE: s = Circle(mid, x, y, ref, e, "CIRCLE"); break;
    }
    return s;
}

void Context::createEditBox()
{
    Shape o = *this->appClickedObject;
    Shape s = Square(o.getCenter(), o.getWidth(), o.getHeight(), -1, o.elem, "SQUARE");
    s.elem.setIsFilled(false);
    s.elem.setLineWeight(1.0f);
    s.elem.setLineColor(Color(0.4, 0.4, 0.4, 0.7));
    this->tempShapes.push_back(s);

    Element e = Element(true, 1.0f, Color(1.0, 0.0, 0.0, 0.7), Color(1.0, 0.0, 0.0, 0.7));

    Point p = o.getCenter();
    p.move(p.getPoint()[0] - o.getWidth()/2, p.getPoint()[1] - o.getHeight()/2);
    Shape c0 = Square(p, 5, 5, -2, e, "SQUARE");
    this->tempShapes.push_back(c0);

    p = o.getCenter();
    p.move(p.getPoint()[0] + o.getWidth()/2, p.getPoint()[1] - o.getHeight()/2);
    Shape c1 = Square(p, 5, 5, -3, e, "SQUARE");
    this->tempShapes.push_back(c1);

    p = o.getCenter();
    p.move(p.getPoint()[0] + o.getWidth()/2, p.getPoint()[1] + o.getHeight()/2);
    Shape c2 = Square(p, 5, 5, -4, e, "SQUARE");
    this->tempShapes.push_back(c2);

    p = o.getCenter();
    p.move(p.getPoint()[0] - o.getWidth()/2, p.getPoint()[1] + o.getHeight()/2);
    Shape c3 = Square(p, 5, 5, -5, e, "SQUARE");
    this->tempShapes.push_back(c3);

    e.setFillColor(Color(0.0, 1.0, 0.0));
    e.setLineColor(Color(0.0, 1.0, 0.0));
    p = o.getCenter();
    p.move(p.getPoint()[0], p.getPoint()[1] + o.getHeight()/2);
    Shape c4 = Square(p, 5, 5, -6, e, "SQUARE");
    this->tempShapes.push_back(c4);
}

void Context::deleteSelectedShape()
{
    if (appClickedObject) {
        int objRef = appClickedObject->getObjRef();
        int n = 0;
        for (int i = 0; i < appShapes.size(); i++) {
            if (appShapes[i].getObjRef() == objRef) {
                n = i;
                break;
            }
        }
        int i = 0;
        vector<Shape>::iterator it;
        for(it=appShapes.begin() ; it < appShapes.end(); it++, i++) {
            if (i == n) {
                appShapes.erase(it);
            }
        }
        appClickedObject = NULL;
        appPrevClickedObject = NULL;
        resetTempShapes();
        glutPostRedisplay();
    }
}

void Context::resetAppShapes()
{
    appShapes = std::vector<Shape>();
}

void Context::resetTempShapes()
{
    tempShapes = std::vector<Shape>();
}

void Context::drawEditBox()
{
    if (appClickedObject && appToolMode == MOVE || appToolMode == ROTATE || appToolMode == RESIZE){
        Point p = appClickedObject->getCenter();
        glPushMatrix();
        //glTranslatef(-300, 0, 0);

        glTranslatef(p.getPoint()[0], 1000 - p.getPoint()[1], 0);
        glRotatef(appClickedObject->getRotation(), 0, 0, 1);

        glTranslatef(-p.getPoint()[0], p.getPoint()[1] - 1000, 0);
        cout << "x : " << p.getPoint()[0] << " y: " << p.getPoint()[1] << "\n";

        for (std::vector<int>::size_type i = 0; i < tempShapes.size(); i++) {
            tempShapes[i].drawShape();
        }

        glPopMatrix();
    } else if (appToolMode == DRAW) {
        for (std::vector<int>::size_type i = 0; i < tempShapes.size(); i++) {
            tempShapes[i].drawShape();
        }
    }
}

void Context::redisplay()
{
    glutPostRedisplay();
}
