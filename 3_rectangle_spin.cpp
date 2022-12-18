#include <iostream>
#include <GL/glut.h>
#include <math.h>
using namespace std;
#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 500
int wid1, wid2, t;
static GLfloat spin = 0.0;

void display() {
    glutSetWindow(t);
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glLoadIdentity();
    glRotatef(spin, 0, 0, 1);
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0);
    glVertex3f(-0.25, -0.25, 0.25);
    glColor3f(0, 1, 0);
    glVertex3f(0.25, -0.25, 0.25);
    glColor3f(0, 0, 1);
    glVertex3f(0.25, 0.25, 0.25);
    glColor3f(1, 0, 1);
    glVertex3f(-0.25, 0.25, 0.25);
    glEnd();
    glPopMatrix();
    if (t == wid1) {
        glFlush(); //the matrix is emptied and the graphics are displayed
        t = wid2;
    }
    else {
        glutSwapBuffers(); //swaps front and back buffers
        t = wid1;
    }
}

void myInit() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glClearColor(1, 1, 1, 1);
    glColor3f(1, 0, 0);
}

void spinRect() {
    spin += 0.5;
    glutPostRedisplay(); //calls the display func
}

void mouse(int button, int state, int x, int y) {
    switch (button) {
    case GLUT_LEFT_BUTTON: if (state == GLUT_DOWN)
        glutIdleFunc(spinRect);
        break;
    case GLUT_RIGHT_BUTTON: if (state == GLUT_DOWN)
        glutIdleFunc(NULL);
        break;
    default: break;
    }
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    wid1 = glutCreateWindow("Single Buffer"); //displays using single buffer mode
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //results in jitter as the entire graphic may not be drawn
    glutDisplayFunc(display);
    myInit();

    glutInitWindowPosition(600, 100);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    wid2 = glutCreateWindow("Double Buffer"); //displays using double buffer mode 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //no lag or jitter experienced
    glutDisplayFunc(display); //2 buffers->(one for on-screen and another for calculating graphics)
    glutMouseFunc(mouse);
    myInit();

    t = wid1;

    glutMainLoop();
    return 0;
}