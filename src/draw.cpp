#include <iostream>
#include <GLUT/glut.h>
#include <vector>
#include <cmath>
#include "Context.h"

#define MOVE 1
#define DRAW 0
#define PICK_TOL 10
#define PICK_BUFFER_SIZE 256


using namespace std;

Context c;


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
    gluOrtho2D(0, 1000, 0, 1000);
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
    c.getTemporyDrawShape()->drawShape();
    cout << "current render mode :" << c.getRenderMode() << "\n";
    cout << "expected render mode :" << GL_RENDER << "\n";
    if (c.getRenderMode() == GL_RENDER) {
        cout << "renderMode: " << c.getRenderMode() << "\n";
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

                c.setTemporyDrawShape(c.newShape(mid, dx, dy, -1));
                glutPostRedisplay();
            }
            break;
        case MOVE:
            if (c.isClicked()) {
                float dx = c.getMouseX() - c.getPrevMouseX();
                float dy = c.getMouseY() - c.getPrevMouseY();
                c.getSelectedObject()->move(dx, dy);
                glutPostRedisplay();
            }
            break;
    }
    c.setPrevMouseX(c.getMouseX());
    c.setPrevMouseY(c.getMouseY());
}

void mouse_click(int button, int state, int x, int y)
{
    c.setMouseX(x);
    c.setMouseY(y);
    c.setPrevMouseX(x);
    c.setPrevMouseY(y);
    switch (c.getToolMode()) {
        case DRAW:
            if (button==GLUT_LEFT_BUTTON) {
                std::cout << "LEFT CLICK @ x: " << x << " y: " << y << "\n";
                if (state==GLUT_DOWN) {
                    c.isClicked(true);
                    c.setInitialDrawPoint(Point(x, y));

                } else if (state==GLUT_UP) {
                    c.isClicked(false);
                    Point mid = c.getInitialDrawPoint()->getMidPoint(Point(x, y));
                    int dx = (c.getInitialDrawPoint()->getPoint()[0] - x);
                    int dy = (c.getInitialDrawPoint()->getPoint()[1] - y);

                    if (c.getInitialDrawPoint()->getDistance(Point(x, y)) < 10.0) {
                        dx = 10;
                        dy = 10;
                    }
                    ////
                    int id = c.getObjectId();
                    c.getShapes()->push_back(c.newShape(mid, dx, dy, id));
                    c.setObjectId(id + 1);
                    c.setTemporyDrawShape(Shape());
                    glutPostRedisplay();
                }
            }
            break;
        case MOVE:
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

                    int maxId = -1;
                    for (int j = 0; j < nitems; j++) {
                        int item = c.getPickBuffer()[index++];

                        cout << "item : " << item << "\n";
                        if (item > maxId) maxId = item;
                    }

                    c.setSelectedObject(maxId);

                }

                if (hits == 0) {
                    c.isClicked(false);
                }

            } else if (state == GLUT_UP) {
                c.isClicked(false);
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
            } else c.setToolMode(DRAW);
            break;
        case 'c': c.resetAppShapes(); glutPostRedisplay(); break;
        case 'v': c.setToolMode(MOVE); break;
    }
}

void drawinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1000, 0, 1000);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

}

void toolinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 100, 0, 500);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
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

    glutMouseFunc(mouse_click);
    glutMotionFunc(mouse_motion);

    c = Context();
    glSelectBuffer(PICK_BUFFER_SIZE, c.getPickBuffer());

    drawinit();

    /*glutInitWindowSize(100, 500);
    glutInitWindowPosition(0, 0);
    w2 = glutCreateWindow("test");
    glutDisplayFunc(display);
    toolinit();*/

    glutSetWindow(w1);
    glutMainLoop();
    return 0;
}
