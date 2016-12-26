#include <iostream>
#include <GLUT/glut.h>
#include <vector>
#include <cmath>
#include "Context.h"
#include <stdlib.h>
#include "Toolbar.h"

#define MOVE 1
#define DRAW 0
#define PICK_TOL 10
#define PICK_BUFFER_SIZE 256
const float RAD_TO_DEG = 180.0/(atan(1)*4);


using namespace std;

Context c;
Toolbar t(&c, 1000, 100);

void reshape(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    c.windowWidth = width;
    c.windowHeight = height;
    cout << "w: " << width << " h: " << height <<"\n";
    gluOrtho2D(0, c.windowWidth, 0, c.windowHeight);
    glutPostRedisplay();
}

void display()
{
    int viewport[4];
    GLint dx = glutGet(GLUT_WINDOW_WIDTH);
    GLint dy = glutGet(GLUT_WINDOW_HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (c.getRenderMode() == GL_SELECT) {
        int viewport;
        glGetIntegerv(GL_VIEWPORT, &viewport);
        std::cout << "got viewport\n";
        gluPickMatrix((double) c.getMouseX(), (double) (dy - c.getMouseY()), PICK_TOL, PICK_TOL, &viewport);
    }
    gluOrtho2D(0, c.windowWidth, 0, c.windowHeight);
    if (c.getRenderMode() == GL_SELECT) {
        glInitNames();
        glPushName(0xffffffff);
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(3.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    for (std::vector<int>::size_type i = 0; i < c.getShapes()->size(); i++) {
        c.appShapes[i].drawShape();
    }

    c.drawEditBox();


    t.draw();
    if (c.getRenderMode() == GL_RENDER) {
        glutSwapBuffers();
    }
}

void mouse_motion(int x, int y)
{
    c.setMouseX(x);
    c.setMouseY(y);
    switch (c.getToolMode()) {
        case DRAW:
            if (c.isClicked()) {
                Point mid = c.getInitialDrawPoint()->getMidPoint(Point(x, y));
                int dx = (c.getInitialDrawPoint()->getPoint()[0] - x);
                int dy = (c.getInitialDrawPoint()->getPoint()[1] - y);
                c.resetTempShapes();
                c.getTempShapes()->push_back(c.newShape(mid, dx, dy, -1));
                glutPostRedisplay();
            }
            break;
        case MOVE:
            if (c.isClicked()) {
                float dx = c.getMouseX() - c.getPrevMouseX();
                float dy = c.getMouseY() - c.getPrevMouseY();
                c.getSelectedObject()->move(dx, dy);
                for (int i = 0; i < c.getTempShapes()->size(); i++) {
                    c.tempShapes[i].move(dx, dy);
                }
                glutPostRedisplay();
            }
            break;
        case ROTATE:
            if (c.isClicked()) {
                Point center = c.getSelectedObject()->getCenter();
                float dx = center.getPoint()[0] - x;
                float dy = center.getPoint()[1] - y;
                float curRot = c.getSelectedObject()->getRotation();
                float angle = RAD_TO_DEG * atan2(dx, dy);
                cout << "angle: " << angle << "\n";
                curRot = angle;
                cout << "rot : " << curRot << "\n";
                c.getSelectedObject()->setRotation(curRot);
                glutPostRedisplay();
            }
            break;

        case RESIZE:
            if (c.isClicked()) {
                Point mid = c.getInitialDrawPoint()->getMidPoint(Point(x, y));
                int dx = (c.getInitialDrawPoint()->getPoint()[0] - x);
                int dy = (c.getInitialDrawPoint()->getPoint()[1] - y);
                c.getSelectedObject()->setCenter(mid);
                c.getSelectedObject()->setSize(dx, dy);
                c.resetTempShapes();
                c.createEditBox();
                glutPostRedisplay();
            }
            break;
    }
    c.setPrevMouseX(c.getMouseX());
    c.setPrevMouseY(c.getMouseY());
}

void handleToolbarClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON){
        c.setRenderMode(GL_SELECT);
        glRenderMode(GL_SELECT);
        display();
        c.setRenderMode(GL_RENDER);
        int NHits = glRenderMode(GL_RENDER);
        std::cout << "toolbar click handler\n";
        std::cout << "NHITS: " << NHits << "\n";

        for (int i = 0, index = 0; i < NHits; i++) {
            int nitems = c.getPickBuffer()[index++];
            int zmin = c.getPickBuffer()[index++];
            int zmax = c.getPickBuffer()[index++];

            for (int j = 0; j < nitems; j++) {
                int item = c.getPickBuffer()[index++];
                std::cout << item << '\n';
                if (item >= 1000000) {
                    t.handleClickEvent(item, state);
                }
                if (item == 999999) {
                    t.deselectAll();
                    glutPostRedisplay();
                }
            }
        }
    }
}

void handleDeleteRequest()
{
    if (c.getToolMode() == MOVE) {
        c.deleteSelectedShape();
    }
}

void handleEditBoxClick(int id) {
    cout << "edit box id " << id <<"\n";
    if (id == -6) {
        c.setToolMode(ROTATE);
    } else if (id < -1) {
        //set to work out which corner is locked
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
        cout << "x, y: " << x << " " << y << "\n";
        c.setInitialDrawPoint(Point(x, y));
        c.setToolMode(RESIZE);
    }
}

void handleMoveClick(int button, int state)
{
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
        c.isClicked(true);
        c.setRenderMode(GL_SELECT);
        glRenderMode(GL_SELECT);
        display();
        c.setRenderMode(GL_RENDER);
        int hits = glRenderMode(GL_RENDER);
        cout << "Number of selected objects: " << hits << " \n";

        for (int i = 0, index = 0; i < hits; i++) {
            int nitems = c.getPickBuffer()[index++];
            int zmin = c.getPickBuffer()[index++];
            int zmax = c.getPickBuffer()[index++];

            int maxId = -6;
            for (int j = 0; j < nitems; j++) {
                int item = c.getPickBuffer()[index++];

                cout << "item : " << item << "\n";
                if (item > maxId) maxId = item;
            }
            if (maxId < 0) {
                handleEditBoxClick(maxId);

            } else {
                cout << "found the obj @ ref " << maxId << "\n";
                c.setSelectedObject(maxId);
                cout << c.getPrevSelectedObject() << "\n";
                cout << c.getSelectedObject() << "\n";
                if (!c.getPrevSelectedObject()) {
                    cout << "prev was null\n";
                    c.resetTempShapes();
                    c.createEditBox();
                } else if ( c.getSelectedObject()->getObjRef() != c.getPrevSelectedObject()->getObjRef()) {
                    cout << "non equal obj\n";
                    c.resetTempShapes();
                    c.createEditBox();
                } else {

                }
            }
        }

        if (hits == 0) {
            c.isClicked(false);
            cout << "nothing clicked";
            c.appClickedObject = NULL;
            c.appPrevClickedObject = NULL;
            c.resetTempShapes();
            t.deselectAll();
        }
        glutPostRedisplay();

    } else if (state == GLUT_UP) {
        c.isClicked(false);
    }
}

void mouse_click(int button, int state, int x, int y)
{
    c.setMouseX(x);
    c.setMouseY(y);
    c.setPrevMouseX(x);
    c.setPrevMouseY(y);

    if (x <= 100) {
        handleToolbarClick(button, state, x, y);
        return;
    }

    switch (c.getToolMode()) {
        case DRAW:
            if (button==GLUT_LEFT_BUTTON) {
                std::cout << "LEFT CLICK @ x: " << x << " y: " << y << "\n";
                if (state==GLUT_DOWN) {
                    c.isClicked(true);
                    c.setInitialDrawPoint(Point(x, y));

                    //***********remove later***********/
                    //float color = (rand() % 255)/255.0f;
                    //c.setLineColor(Color(color, color, color));
                    /***********************************/

                } else if (state==GLUT_UP) {

                    t.deselectAll();
                    c.isClicked(false);
                    Point mid = c.getInitialDrawPoint()->getMidPoint(Point(x, y));
                    int dx = (c.getInitialDrawPoint()->getPoint()[0] - x);
                    int dy = (c.getInitialDrawPoint()->getPoint()[1] - y);

                    if (c.getInitialDrawPoint()->getDistance(Point(x, y)) < 10.0) {
                        dx = 10;
                        dy = 10;
                    }

                    int id = c.getObjectId();
                    c.getShapes()->push_back(c.newShape(mid, dx, dy, id));
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
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'q': exit(0); break;
        case 's':
            if (c.getToolMode() == DRAW ) {
                c.setShapeToDraw((c.getShapeToDraw()+ 1) % 3);
                glutPostRedisplay();
            } else {
                c.setToolMode(DRAW);
                t.setDrawMode();
                c.resetTempShapes();
                glutPostRedisplay();
            }
            break;
        case 'c': c.resetAppShapes(); glutPostRedisplay(); break;
        case 'v': c.setToolMode(MOVE); t.setMoveMode(); glutPostRedisplay(); break;
        case 'd': handleDeleteRequest(); break;
    }
}

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
    GLint w1, w2;
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
