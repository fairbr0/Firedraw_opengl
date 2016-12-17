#include "Shape.h"
#include <Vector>
#include <GLUT/glut.h>
#include "Color.h"

#define MOVE 1
#define DRAW 0

#define SQUARE 0
#define TRIANGLE 1
#define CIRCLE 2

#define PICK_TOL 5
#define PICK_BUFFER_SIZE 256

class Context
{
public:
    Context();
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
    Shape* appClickedObject;
    Shape drawTemporyShape;
    std::vector<Shape> appShapes;
    Point drawInitialPoint;
    Color appLineColor;
    Color appFillColor;
    float appLineWeight;
    bool appFillShape;

    void setSelectedObject(int id);
    void setShapeToDraw(int id);
    void setToolMode(int tool);
    void setMouseX(float x);
    void setMouseY(float y);
    void setPrevMouseX(float x);
    void setPrevMouseY(float y);
    void setRenderMode(int renderMode);
    void setTemporyDrawShape(Shape s);
    void setInitialDrawPoint(Point p);
    void isClicked(bool clicked);
    void setObjectId(int id);
    void setLineColor(Color c);
    void setFillColor(Color c);
    void setLineWeight(float w);
    void setIsFilled(bool b);

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
    Shape* getTemporyDrawShape();
    Point* getInitialDrawPoint();
    std::vector<Shape> * getShapes();

    Shape newShape(Point mid, int x, int y, int ref);
    void resetAppShapes();
private:
};
