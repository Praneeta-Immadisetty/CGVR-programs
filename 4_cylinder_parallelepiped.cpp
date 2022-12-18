#include <iostream>
#include <GL/glut.h>
#include <math.h>
using namespace std;
#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 500
int wid1, wid2, xc, yc, r, ht, xp, yp, l, b, h;

///////////////// Cylinder /////////////////

void plot_circle_points(int xc, int yc, int x, int y, int base) { //replicate for other 7 octants
    if (base) {
        glColor3f(0, 0, 1);
    }
    else {
        glColor3f(0, 1, 1);
    }
    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc - y, yc - x);
    glEnd();
}

void draw_circle(int xc, int yc, int r, int base) { //bresenham's circle
    int x = 0, y = r;
    int d = 3 - 2 * r; //decision param
    while (x < y) { //45-90 octant
        plot_circle_points(xc, yc, x, y, base);
        x++;
        if (d < 0) {
            d += 4 * x + 6;
        }
        else {
            y--;
            d += 4 * (x - y) + 10;
        }
        plot_circle_points(xc, yc, x, y, base);
    }
    glFlush();
}

void display_cylinder() {
    glutSetWindow(wid1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 1);
    //xc = 250, yc = 150, r = 50, ht = 100;
    for (int i = 0; i < ht; i+=5) { //to see distinct rings i+=5
        draw_circle(xc, yc + i, r, 0);
    }
    for (int i = r; i >= 0; i--) { //fill the base
        draw_circle(xc, yc + ht, i, 1);
    }
    glFlush();
}

///////////////// Parallelepiped /////////////////

void draw_quad(int x, int y, int l, int b, int face) {
    if (face) {
        glBegin(GL_LINE_LOOP);
        glColor3f(1, 1, 0);
        glVertex2i(x, y);
        glVertex2i(x + l, y);
        glColor3f(1, 0, 0);
        glVertex2i(x + l, y + b);
        glVertex2i(x, y + b);
        glEnd();
    }
    else {
        glBegin(GL_LINE_LOOP);
        glColor3f(1, 1, 0);
        glVertex2i(x, y);
        glColor3f(1, 0, 0);
        glVertex2i(x + l, y);
        glColor3f(1, 1, 0);
        glVertex2i(x + l, y + b);
        glColor3f(1, 0, 0);
        glVertex2i(x, y + b);
        glEnd();
    }
}

void display_parallelopiped() {
    glutSetWindow(wid2);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    //xp = 100, yp = 100, l = 100, b = 50, h = 150;
    for (int i = 0; i < h; i+=5) {
        draw_quad(xp + i, yp + i, l, b, 0);
    }
    for (int i = l, j = b; i>=0 && j>=0; i--, j--) {
        draw_quad(xp, yp, i, j, 1);
    }
    glFlush();
}

void myInit() {
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glClearColor(1, 1, 1, 1);
    glColor3f(1, 0, 0);
}

int main(int argc, char* argv[]) {
    printf_s("Enter for cylinder: (xc, yc), r, ht: ");
    scanf_s("%d%d%d%d", &xc, &yc, &r, &ht);
    printf_s("Enter for parallelepiped: (xp, yp), l, b, h: ");
    scanf_s("%d%d%d%d%d", &xp, &yp, &l, &b, &h);
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    wid1 = glutCreateWindow("Cylinder");
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutDisplayFunc(display_cylinder);
    myInit();

    glutInitWindowPosition(600, 100);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    wid2 = glutCreateWindow("Parallelepiped");
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutDisplayFunc(display_parallelopiped);
    myInit();

    glutMainLoop();
    return 0;
}