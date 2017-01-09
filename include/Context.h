#pragma once
#include "Shape.h"
#include <vector>
#ifdef __APPLE__
#include <GLUT/glut.h> 
#else
#include <GL/glut.h> 
#endif
#include "Color.h"
#include "Text.h"
#include "Line.h"

#define DRAW 0
#define MOVE 1
#define RESIZE 2
#define ROTATE 3
#define POPOVER 4

#define SQUARE 0
#define TRIANGLE 1
#define CIRCLE 2
#define LINE 3

#define SAVE_POPUP 0
#define LOAD_POPUP 1
#define TEXT_POPUP 2

#define PICK_TOL 5
#define PICK_BUFFER_SIZE 256

class Context
{
public:
    Context();
    bool colorToChange = true;
    bool appIsClicked;
    int appShapeToDraw;
    int appRenderMode;
    int mouse_x;
    int mouse_y;
    int mouse_prev_x;
    int mouse_prev_y;
    int appToolMode;
    int appNextObjectId;
    unsigned int PickBuffer[PICK_BUFFER_SIZE];
    Shape* appClickedObject = NULL;
    Line tempLine;
    std::vector<Shape> tempShapes;
    std::vector<Shape> appShapes;
    std::vector<Text> appTexts;
    std::vector<Line> appLines;
    Point drawInitialPoint;
    Color appLineColor;
    Color appFillColor;
    float appLineWeight;
    bool appFillShape;
    Shape* appPrevClickedObject = NULL;
    int windowHeight, windowWidth;
    bool appKeyboardCaptured = false;

    void setSelectedObject(int id);
    void setShapeToDraw(int id);
    void setToolMode(int tool);
    void setMouseX(float x);
    void setMouseY(float y);
    void setPrevMouseX(float x);
    void setPrevMouseY(float y);
    void setRenderMode(int renderMode);
    void setInitialDrawPoint(Point p);
    void isClicked(bool clicked);
    void setObjectId(int id);
    void setLineColor(Color c);
    void setFillColor(Color c);
    void setLineWeight(float w);
    void setIsFilled(bool b);
    void setPrevSelectedObject(Shape *);
    void setColor(Color c);
    void setShapes(std::vector<Shape> shapes);
    void increaseAlpha();
    void decreaseAlpha();
    void setCreatePopup(int type);
    void setKeyboardCaptured(bool b);
    void setTempLine(Line l);

    unsigned int* getPickBuffer();
    bool isClicked();
    int getRenderMode();
    float getMouseX();
    float getMouseY();
    float getPrevMouseX();
    float getPrevMouseY();
    int getToolMode();
    int getShapeToDraw();
    int getObjectId();
    float getLineWeight();
    bool getIsFilled();
    Color* getLineColor();
    Color* getFillColor();
    Shape* getSelectedObject();
    Shape* getPrevSelectedObject();
    Point* getInitialDrawPoint();
    std::vector<Shape> * getShapes();
    std::vector<Shape> * getTempShapes();
    int getNewPopoverType();
    bool checkShoulCreatePopup();
    bool getKeyboardCaptured();
    Line getTempLine();

    Shape newShape(Point mid, int x, int y, int ref);
    void deleteSelectedShape();
    void resetAppShapes();
    void resetTempShapes();
    void createEditBox();
    void drawEditBox();
    void redisplay();
    void addText(string text);
    void setProperties();
    Line newLine(Point p1, Point p2, int ref);
private:
    bool createPopup;
    int newPopupType;
};
