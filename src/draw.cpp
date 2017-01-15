#include <iostream>
#include <vector>
#include <cmath>
#include "Context.h"
#include <stdlib.h>
#include "Toolbar.h"
#include "Popover.h"
#include "Callbacks.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define MOVE 1
#define DRAW 0
#define PICK_TOL 10
#define PICK_BUFFER_SIZE 256
const float RAD_TO_DEG = 180.0/(atan(1)*4);
const float DEG_TO_RAD = (atan(1)*4) / 180;


using namespace std;

//main application program. Instantiates the application state machine, toolbar and views.

Context c;
Toolbar t(&c, 1000, 100);
Popover popover;
bool lineEnd;

//reshape function for when window size increased. Window is locked at 1000x1000.
void reshape(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    c.windowWidth = 1000;
    c.windowHeight = 1000;
    //glViewPort(0, 0, width, height);
    gluOrtho2D(0, c.windowWidth, 0, c.windowHeight);

    glutReshapeWindow(c.windowWidth, c.windowHeight);

    glutPostRedisplay();
}

//create a popover object of the desired type in the context
void setPopover()
{
    int type = c.getNewPopoverType();
    switch (type) {
        case SAVE_POPUP:
            popover = Popover(&c, &t.callbacks, &Callbacks::popover_saveCallBack, &Callbacks::popover_cancelCallBack, "Save", "Save", "Enter name of file to save:");
            t.setMoveMode();
            break;
        case LOAD_POPUP:
            popover = Popover(&c, &t.callbacks, &Callbacks::popover_loadCallBack, &Callbacks::popover_cancelCallBack, "Load", "Load", "Enter name of file to open:");
            t.setMoveMode();
            break;
        case TEXT_POPUP:
            popover = Popover(&c, &t.callbacks, &Callbacks::popover_textCallBack, &Callbacks::popover_cancelCallBack, "Create", "Text", "Enter text to add to drawing:");
            t.setMoveMode();
            break;
    }
}

//draw the application shapes in depth order.
void drawShapes() {
    int i = 0;
    int j = 0;
    int k = 0;
    int size = c.getShapes()->size() + c.appTexts.size() + c.appLines.size();
    //go through all shapes.
    for (int n = 0 ; n < size; n++) {
        int t = 0;
        int max = 500000;

        int curRef = 0;
        //find the net obj to draw by looking at next element on each vecotr.
        if (i < c.getShapes()->size()) {
            curRef = c.appShapes[i].getObjRef();
            if (curRef < max) {
                max = curRef;
            }
        }
        if (j < c.appTexts.size()) {
            curRef = c.appTexts[j].getObjRef();
            if (curRef < max) {
                max = curRef;
                t = 1;
            }
        }
        if (k < c.appLines.size()) {
            curRef = c.appLines[k].getObjRef();
            if (curRef < max) {
                max = curRef;
                t = 2;
            }
        }
        //draw the next element
        if (t == 0) {
            c.appShapes[i].drawShape();
            i++;
        } else if (t == 1) {
            c.appTexts[j].drawShape();
            j++;
        } else {
            c.appLines[k].drawShape();
            k++;
        }
    }
}

//main application display function.
void display()
{

    GLint viewport[4];

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    // if in select mode, only draw area around the mouse, and use the pick matrix to add object references to the pick buffer
    if (c.getRenderMode() == GL_SELECT) {
        glGetIntegerv(GL_VIEWPORT, viewport);

        glInitNames();
        glPushName(0xffffffff);

        gluPickMatrix((double) c.getMouseX(), (double) (c.getMouseY()), PICK_TOL, PICK_TOL, viewport);
    }
    //clean up after picking
    gluOrtho2D(0, c.windowWidth, 0, c.windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glFlush();
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(3.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    //draw shapes
    drawShapes();
    //draw bounding box
    c.drawEditBox();
    //draw toolbar
    t.draw();
    //draw popover if needed
    if (c.getToolMode() == POPOVER) {
        if (c.checkShoulCreatePopup() != false) {
            setPopover();
        }
        popover.display();
    }
    //display if the render mode is render. Wont display on a click
    if (c.getRenderMode() == GL_RENDER) {
        glutSwapBuffers();
    }
}

//function to handle mouse movement
void mouse_motion(int x, int y)
{
    c.setMouseX(x);
    c.setMouseY(1000 - y);
    switch (c.getToolMode()) {
        case DRAW:
            //onyl care if mouse is clicked
            if (c.isClicked()) {
                //draw tempry shaped while moving so user can see what they are drawing.
                if (c.getShapeToDraw() == LINE) {
                    c.resetTempShapes();
                    c.setTempLine(c.newLine(*c.getInitialDrawPoint(), Point(x, c.getMouseY()), -1));
                    glutPostRedisplay();
                } else {
                    Point mid = c.getInitialDrawPoint()->getMidPoint(Point(x, c.getMouseY()));
                    int dx = (c.getInitialDrawPoint()->getPoint()[0] - x);
                    int dy = (c.getInitialDrawPoint()->getPoint()[1] - c.getMouseY());
                    if (dy < 0) dy = dy * -1;
                    c.resetTempShapes();
                    c.getTempShapes()->push_back(c.newShape(mid, dx, dy, -1));
                    glutPostRedisplay();
                }
            }
            break;
        case MOVE:
            //move the selected object and its bounding box
            if (c.isClicked()) {
                float dx = c.getMouseX() - c.getPrevMouseX();
                float dy = c.getMouseY() - c.getPrevMouseY();
                if (c.getSelectedObject()->getType() == "LINE") {
                    Line* l = (Line*)c.getSelectedObject();
                    l->move(dx, dy);
                } else {
                    c.getSelectedObject()->move(dx, dy);
                } for (int i = 0; i < c.getTempShapes()->size(); i++) {
                    c.tempShapes[i].move(dx, dy);
                }
                glutPostRedisplay();
            }
            break;
        case ROTATE:
            //rotate the object around its center, based off mouse location.
            if (c.isClicked()) {
                Point center = c.getSelectedObject()->getCenter();
                float dx = center.getPoint()[0] - x;
                float dy = -1 * (center.getPoint()[1] - c.getMouseY());
                float curRot = c.getSelectedObject()->getRotation();
                float angle = RAD_TO_DEG * atan2(dx, dy);
                curRot = angle;
                c.getSelectedObject()->setRotation(curRot);
                glutPostRedisplay();
            }
            break;

        case RESIZE:
            if (c.isClicked()) {
                // if line point selected, move it and redraw the line
                if (c.getSelectedObject()->getType() == "LINE") {
                    Point p(c.getMouseX(), c.getMouseY());
                    if (lineEnd) c.getSelectedObject()->setCenter(p);
                    else c.getSelectedObject()->setEnd(p);
                    c.resetTempShapes();
                    c.createEditBox();

                } else {
                    //set rotation to 0.
                    c.getSelectedObject()->setRotation(0.0);
                    Point midpoint = c.getInitialDrawPoint()->getMidPoint(Point(x, c.getMouseY()));
                    //set the new width and height
                    int dx = (c.getInitialDrawPoint()->getPoint()[0] - x);
                    int dy = (c.getInitialDrawPoint()->getPoint()[1] - c.getMouseY());
                    if (dy < 0) dy *= -1;
                    if (dx < 0) dx *= -1;
                    c.getSelectedObject()->setCenter(midpoint);
                    c.getSelectedObject()->setSize(dx, dy);
                    c.resetTempShapes();
                    c.createEditBox();
                }

                glutPostRedisplay();
            }
            break;
    }
    //remember previous mouse location
    c.setPrevMouseX(c.getMouseX());
    c.setPrevMouseY(c.getMouseY());
}

//handle a click within the toolbar region
void handleToolbarClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON){
        //set render mode to select.
        c.setRenderMode(GL_SELECT);
        glRenderMode(GL_SELECT);
        //display to fill pick buffer with obj refs for objs under the mouse cursor.
        display();
        //set render mode back to render. Get number of objects clicked.
        c.setRenderMode(GL_RENDER);
        int NHits = glRenderMode(GL_RENDER);

        //fire click event for the selected item if its a button
        for (int i = 0, index = 0; i < NHits; i++) {
            int nitems = c.getPickBuffer()[index++];
            int zmin = c.getPickBuffer()[index++];
            int zmax = c.getPickBuffer()[index++];

            for (int j = 0; j < nitems; j++) {
                int item = c.getPickBuffer()[index++];
                //fire click event on the selected item.
                if (item >= 1000000) {
                    t.handleClickEvent(item, state);
                }
                //didnt click a button, deselect all buttons
                if (item == 999999) {
                    t.deselectAll();
                    glutPostRedisplay();
                }
            }
        }
    }
}

//handle click event on a popover object
void handlePopoverClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON){
        //set render mode to select
        c.setRenderMode(GL_SELECT);
        glRenderMode(GL_SELECT);
        //display to fill pick buffer with obj refs for objs under the mouse cursor.
        display();
        //set render mode back to render. Get number of objects clicked.
        c.setRenderMode(GL_RENDER);
        int NHits = glRenderMode(GL_RENDER);

        //fire popover click event.
        for (int i = 0, index = 0; i < NHits; i++) {
            int nitems = c.getPickBuffer()[index++];
            int zmin = c.getPickBuffer()[index++];
            int zmax = c.getPickBuffer()[index++];

            for (int j = 0; j < nitems; j++) {
                int item = c.getPickBuffer()[index++];
                if (item >= 2000000) {
                    popover.handleClickEvent(item, state);
                }
            }
        }
    }
}

//delete a selected shape
void handleDeleteRequest()
{
    if (c.getToolMode() == MOVE) {
        c.deleteSelectedShape();
    }
}

//handle click on the bounding box.
void handleEditBoxClick(int id) {
    if (id == -6) {
        //green square selected. Enter rotate mode
        c.setToolMode(ROTATE);
    } else if (id < -1) {
        //detect if clicked item was a line or not. If so, set which end was pressed.
        if (c.getSelectedObject()->getType() == "LINE") {
            if (id == -2)
                lineEnd = true;
            else
                lineEnd = false;
        } else {
            //lock opposite corner to the one which was selected, resize around that corner.
            float height = c.getSelectedObject()->getHeight();
            float width = c.getSelectedObject()->getWidth();
            Point p = c.getSelectedObject()->getCenter();
            float x = 0;
            float y = 0;
            switch (id) {
                case -2:
                    x = p.getPoint()[0] + width / 2;
                    y = p.getPoint()[1] + height / 2;
                    break;
                case -3:
                    x = p.getPoint()[0] - width / 2;
                    y = p.getPoint()[1] + height / 2;
                    break;
                case -4:
                    x = p.getPoint()[0] - width / 2;
                    y = p.getPoint()[1] - height / 2;
                    break;
                case -5:
                    x = p.getPoint()[0] + width / 2;
                    y = p.getPoint()[1] - height / 2;
                    break;
            }
            c.setInitialDrawPoint(Point(x, y));
        }
        //enter resize mode
        c.setToolMode(RESIZE);
    }
}

//click handler for the canvas area.
void handleMoveClick(int button, int state)
{

    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
        //get the references under the mouse
        c.isClicked(true);
        c.setRenderMode(GL_SELECT);
        glRenderMode(GL_SELECT);
        display();
        c.setRenderMode(GL_RENDER);
        int hits = glRenderMode(GL_RENDER);
        //find the highest reference object, select that.
        //if nothing clicked, remove bounding boxes, tempory shapes, selected pointers
        if (hits == 0) {
            c.isClicked(false);
            c.appClickedObject = NULL;
            c.appPrevClickedObject = NULL;
            c.resetTempShapes();
            t.deselectAll();
        } else {

            int maxId = 0;
            int minId = -1;
            for (int i = 0, index = 0; i < hits; i++) {
                int nitems = c.getPickBuffer()[index++];
                int zmin = c.getPickBuffer()[index++];
                int zmax = c.getPickBuffer()[index++];


                for (int j = 0; j < nitems; j++) {
                    int item = c.getPickBuffer()[index++];

                    if (item > maxId) maxId = item;
                    if (item < minId) minId = item;
                }

            }
            if (minId < -1) {
                //bounding box node was clicked
                handleEditBoxClick(minId);
            } else {
                //a shape was clicked. set it as selected
                c.setSelectedObject(maxId);
                //if there was a previous object, not equal to this one, delete all temp shapes
                if (!c.getPrevSelectedObject()) {
                    c.resetTempShapes();
                    c.createEditBox();
                } else if ( c.getSelectedObject()->getObjRef() != c.getPrevSelectedObject()->getObjRef()) {
                    c.resetTempShapes();
                    c.createEditBox();
                } else {

                }
            }
        }
        glutPostRedisplay();

    } else if (state == GLUT_UP) {
        c.isClicked(false);
    }
}

//main click handler.
void mouse_click(int button, int state, int x, int y)
{
    //save mouse coordinates in context
    c.setMouseX(x);
    c.setMouseY(1000 - y);
    c.setPrevMouseX(x);
    c.setPrevMouseY(1000 - y);

    //detecct if in toolbar area
    if (x <= 100) {
        handleToolbarClick(button, state, x, y);
        return;
    }

    switch (c.getToolMode()) {
        case DRAW:
            //if in draw mode, click down, set inital draw point.
            if (button==GLUT_LEFT_BUTTON) {
                if (state==GLUT_DOWN) {
                    c.isClicked(true);
                    c.setInitialDrawPoint(Point(x, c.getMouseY()));

                } else if (state==GLUT_UP) {
                    //if letting go, create a new shape to selected tool type.
                    t.deselectAll();
                    c.isClicked(false);

                    int id = c.getObjectId();
                    if (c.getShapeToDraw() == LINE) {
                        c.appLines.push_back(c.newLine(*c.getInitialDrawPoint(), Point(x, c.getMouseY()), id));
                    } else {
                        Point mid = c.getInitialDrawPoint()->getMidPoint(Point(x,  c.getMouseY()));
                        int dx = (c.getInitialDrawPoint()->getPoint()[0] - x);
                        int dy = (c.getInitialDrawPoint()->getPoint()[1] - c.getMouseY());
                        if (dy < 0) dy *= -1;

                        //minimum shape size is 10x10 pixels
                        if (c.getInitialDrawPoint()->getDistance(Point(x, c.getMouseY())) < 10.0) {
                            dx = 10;
                            dy = 10;
                        }

                        c.getShapes()->push_back(c.newShape(mid, dx, dy, id));
                    }
                    //increment depth for next object
                    c.setObjectId(id + 1);
                    c.resetTempShapes();
                    glutPostRedisplay();
                }
            }
            break;
        case MOVE:
            handleMoveClick(button, state);
            break;
        case RESIZE:
            if (state == GLUT_UP) {
                c.setToolMode(MOVE);
                //lock in the resize
            }
            break;
        case ROTATE:
            if (state == GLUT_UP) {
                c.setToolMode(MOVE);
            }
            break;
        case POPOVER:
            handlePopoverClick(button, state, x, y);
    }
}

//keyboard handler function for shortcuts.
void keyboard(unsigned char key, int x, int y)
{
    //if keyboard captured, send char to the popover.
    if (c.getToolMode() == POPOVER && c.getKeyboardCaptured() == true) {
        popover.addChar(key);
        return;
    }
    //fire shortcuts.
    switch (key) {
        case 'q': exit(0); break;
        case 's':
            if (c.getToolMode() == DRAW ) {
                c.setShapeToDraw((c.getShapeToDraw()+ 1) % 3);
                glutPostRedisplay();
            } else {
                c.setToolMode(DRAW);
                t.setDrawMode();
                c.appClickedObject = NULL;
                c.resetTempShapes();
                glutPostRedisplay();
            }
            break;
        case 'c': c.resetAppShapes(); glutPostRedisplay(); break;
        case 'v': c.setToolMode(MOVE); t.setMoveMode(); glutPostRedisplay(); break;
        case 'd': handleDeleteRequest(); break;
    }
}

//initial application graphics setup.
void drawinit()
{
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    c.windowWidth = 1000;
    c.windowHeight = 1000;
    gluOrtho2D(0, c.windowWidth, 0, c.windowHeight);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

}

int main(int argc, char* argv[])
{
    GLint w1;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 0);
    w1 = glutCreateWindow("Firedraw");
    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);

    glutMouseFunc(mouse_click);
    glutMotionFunc(mouse_motion);

    cout << "creating Context\n";
    c = Context();
    glSelectBuffer(PICK_BUFFER_SIZE, c.getPickBuffer());
    cout << "context created\n";
    drawinit();

    glutSetWindow(w1);
    glutMainLoop();
    return 0;
}
