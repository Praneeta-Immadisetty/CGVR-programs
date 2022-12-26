#include<stdlib.h>
#include<iostream>
#include<GL/glut.h>
using namespace std;

#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 500

int x1, x2, yc1, y2, flag = 0;

// function to draw a pixel
void drawPixel(int x, int y) {
	glColor3f(0, 0, 1); //blue
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

// function to draw line using Bresenham's line drawing algorithm
void drawLine() {
	//glClear(GL_COLOR_BUFFER_BIT); //mentioning this will create new line on cleared window
	int dx, dy, i, e, incx = 1, incy = 1, inc1, inc2, x, y;
	dx = x2 - x1;
	dy = y2 - yc1;
	if (dx == 0) { //vertical line
		for (i = 0; i <= dy; i++)
			drawPixel(x1, yc1 + i);
		return;
	}
	if (dy == 0) { //horizontal line
		for (i = 0; i <= dx; i++)
			drawPixel(x1 + i, yc1);
		return;
	}
	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	if (x2 < x1) incx = -1;
	if (y2 < yc1) incy = -1;
	x = x1;
	y = yc1;
	if (dx > dy) { //m<1 increments of x
		drawPixel(x, y);
		e = 2 * dy - dx; //initial decision parameter
		inc1 = 2 * (dy - dx); //decision parameter > 0
		inc2 = 2 * dy; //decision parameter <=0
		for (i = 0; i < dx; i++) {
			if (e > 0) {
				y = y + incy;
				e = e + inc1;
			}
			else
				e = e + inc2;
			x = x + incx;
			drawPixel(x, y);
		}
	}
	else {//m>1 swap x and y
		drawPixel(x, y);
		e = 2 * dx - dy;
		inc1 = 2 * (dx - dy);
		inc2 = 2 * dx;
		for (i = 0; i < dy; i++) {
			if (e > 0) {
				x = x + incx;
				e = e + inc1;
			}
			else
				e = e + inc2;
			y = y + incy;
			drawPixel(x, y);
		}
	}
	glFlush();
}

void myInit() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	glPointSize(5);
	gluOrtho2D(-250, 250, -250, 250); //gluOrtho2D() sets up a two-dimensional orthographic viewing region
}

void mouseFunc(int button, int state, int x, int y) { //The x and y callback parameters indicate the window
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { //relative coordinates when the mouse button state changed.
		if (flag == 0) { //1st pt
			cout << "x1, y1 : ";
			x1 = x - 250; // convert to ortho coordinate system
			yc1 = 250 - y;
			flag++;
			cout << x1 << " " << yc1 << " \n";
		}
		else {
			cout << "x2, y2 : ";
			x2 = x - 250;
			y2 = 250 - y;
			flag = 0;
			cout << x2 << " " << y2 << " \n";
			drawLine();
		}
	}
}

void display() {}

int main(int argc, char** argv) {
	int choice;
	cout << "Enter 1 for keyboard and 2 for mouse \n";
	cin >> choice;
	if (choice == 1) {
		cout << "Enter (x1, y1), (x2, y2) : ";
		cin >> x1 >> yc1 >> x2 >> y2;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Line Drawing");
	if (choice == 2) {
		glutMouseFunc(mouseFunc);
		glutDisplayFunc(display);
		//myInit();
	}
	else {
		glutDisplayFunc(drawLine);
		//myInit();
	}
	myInit();
	glutMainLoop();
}