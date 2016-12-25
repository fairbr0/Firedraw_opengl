#include <GLUT/glut.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "Point.h"
#include "Toolbar.h"


#define PICK_TOL 10
#define PICK_BUFFER_SIZE 256

unsigned int PickBuffer[PICK_BUFFER_SIZE];

void changeColor();

int renderMode = GL_RENDER;
int NHits;
int mouse_x, mouse_y;
int count = 0;

Context c;
Toolbar t(&c);

void changeColor()
{
    std::cout << "callback\n";
    float color = (rand() % 255) / 255.0f;
    glColor3f(color, color, color);
    glutPostRedisplay();
}

void drawSquare(int id)
{
    glLoadName(id);
    glBegin(GL_POLYGON);
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.5, -0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(-0.5, 0.5);
    glEnd();
}

void draw() {

    glMatrixMode(GL_MODELVIEW);
    glLineWidth(2.0f);


    t.draw();

}

void display()
{
    int viewport[4];

    GLint dx = glutGet(GLUT_WINDOW_WIDTH);
    GLint dy = glutGet(GLUT_WINDOW_HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (renderMode == GL_SELECT) {
        int viewport;
        glGetIntegerv(GL_VIEWPORT, &viewport);
        gluPickMatrix((double) mouse_x, (double) (dy - mouse_y), PICK_TOL, PICK_TOL, &viewport);
    }
    gluOrtho2D(0, 100, 0, 600);
    if (renderMode == GL_SELECT) {
        glInitNames();
        glPushName(0xffffffff);
    }

    draw();

    if (renderMode == GL_RENDER) {
        glutSwapBuffers();
    }
}

void mouse_click(int button, int state, int x, int y) {
    mouse_x = x;
    mouse_y = y;
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
        renderMode = GL_SELECT;
        glRenderMode(GL_SELECT);
        display();
        renderMode = GL_RENDER;
        NHits = glRenderMode(GL_RENDER);
        std::cout << "NHITS: " << NHits << "\n";

        for (int i = 0, index = 0; i < NHits; i++) {
            int nitems = PickBuffer[index++];
            int zmin = PickBuffer[index++];
            int zmax = PickBuffer[index++];

            for (int j = 0; j < nitems; j++) {
                int item = PickBuffer[index++];
                std::cout << item << '\n';
                if (item >= 1000000) {
                    t.handleClickEvent(item, state);
                }
            }
        }

    } else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP)) {
        renderMode = GL_SELECT;
        glRenderMode(GL_SELECT);
        display();
        renderMode = GL_RENDER;
        NHits = glRenderMode(GL_RENDER);
        std::cout << "NHITS: " << NHits << "\n";

        for (int i = 0, index = 0; i < NHits; i++) {
            int nitems = PickBuffer[index++];
            int zmin = PickBuffer[index++];
            int zmax = PickBuffer[index++];

            for (int j = 0; j < nitems; j++) {
                int item = PickBuffer[index++];
                std::cout << item << '\n';
                if (item >= 1000000) {
                    t.handleClickEvent(item, state);
                }
            }
        }
    }
}

void drawinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 100, 0, 600);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glColor3f(1.0f, 0.0f, 0.0f);

}

int main(int argc, char *argv[])
{
    GLint win;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(100, 600);
    glutInitWindowPosition(50, 50);
    win = glutCreateWindow("ToolBar");
    glutDisplayFunc(display);
    glutMouseFunc(mouse_click);

    glSelectBuffer(PICK_BUFFER_SIZE, PickBuffer);

    drawinit();
    glutMainLoop();
}
