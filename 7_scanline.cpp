#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <Windows.h>
#include <GL/glut.h>
#define MAX_POINTS 100
using namespace std;

int m = 0, n = 0;
typedef float point[2];
point p[MAX_POINTS];
static float intx[10] = { 0 };

// Draw a line between 2 points with delay
void drawLine(float x1, float y1, float x2, float y2) {
    Sleep(1);
    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
    glFlush();
}

// Detect an edge and add the x-intersections into an array using y = mx+c => x = x0 + (y-y0)/m
void edgeDetect(float x1, float y1, float x2, float y2, int scanline) {
    float temp;
    if (y2 < y1) {
        temp = y1;
        y1 = y2;
        y2 = temp;
        temp = x1;
        x1 = x2;
        x2 = temp;
    }
    if (scanline > y1 && scanline < y2) {
        intx[m++] = x1 + (x2 - x1) * (scanline - y1) / (y2 - y1);
    }
}

// Draw a line between alternate points to fill the polygon
void scanFill(point p[]) {
    for (int s1 = 0; s1 <= 500; s1++) {
        m = 0;
        for (int i = 0; i < n; i++) {
            edgeDetect(p[i][0], p[i][1], p[(i + 1) % n][0], p[(i + 1) % n][1], s1);
        }
        std::sort(intx, intx + m);
        if (m >= 2) {
            for (int i = 0; i < m - 1; i += 2) {
                drawLine(intx[i], s1, intx[i + 1], s1);
            }
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < n; i++) { //vertices of the polygon
        glVertex2fv(p[i]);
    }
    glEnd();
    scanFill(p);
    glFlush();
}

void idle() {
    glutPostRedisplay();
}

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char* argv[]) {
    // x1=200;y1=200;x2=100;y2=300;x3=200;y3=400;x4=300;y4=300;
    // exception x1=150, y1=150, x2=150, y2=300, x3=300, y3=300, x4=300, y4=150, x5=200, y5=400
    cout << "Enter the number of points: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Enter the x and y coordinates of point " << i + 1 << ": ";
        cin >> p[i][0] >> p[i][1];
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Scan Line");
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    myInit();
    glutMainLoop();
    return 0;
}