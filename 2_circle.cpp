#include <GL/glut.h>
#include <iostream>
#include <math.h>
using namespace std;

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

int xc, yc, r, p1_x, p2_x, p1_y, p2_y, flag = 0;

void draw_circle(int xc, int yc, int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(xc + x, yc + y);
	glVertex2i(xc - x, yc + y);
	glVertex2i(xc + x, yc - y);
	glVertex2i(xc - x, yc - y);
	glVertex2i(xc + y, yc + x);
	glVertex2i(xc - y, yc + x);
	glVertex2i(xc + y, yc - x);
	glVertex2i(xc - y, yc - x);
	glEnd();
}

void circleBres() {
	glClear(GL_COLOR_BUFFER_BIT);
	int x = 0, y = r;
	int d = 3 - 2 * r;
	while (x <= y) {
		draw_circle(xc, yc, x, y);
		x++;
		if (d < 0) //east
			d = d + 4 * x + 6;
		else { //southeast
			y--;
			d = d + 4 * (x - y) + 10;
		}
		draw_circle(xc, yc, x, y);
	}
	glFlush();
}

void mouseFuncCircle(int button, int state, int x, int y) { 
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (flag == 0) { //centre
			p1_x = x - 250; // convert to ortho coordinate system
			p1_y = 250 - y;
			flag++;
		} 
		else { //cal radius
			float exp;
			p2_x = x - 250;
			p2_y = 250 - y;
			flag = 0;
			xc = p1_x;
			yc = p1_y;
			exp = (p2_x - p1_x) * (p2_x - p1_x) + (p2_y - p1_y) * (p2_y - p1_y);
			r = (int)(sqrt(exp)); //euclidean dist
			circleBres();
		}
	}
}

void drawingCircle() {}

void myInit() {
	glClearColor(1, 1, 1, 1);
	glColor3f(0.0, 1.0, 0.0);
	glPointSize(3.0);
	gluOrtho2D(-250, 250, -250, 250);
}

int main(int argc, char** argv) {
	int choice;
	cout << "Enter 1 for keyboard and 2 for mouse \n";
	cin >> choice;
	if (choice == 1) {
		cout << "Enter (xc, yc), r : ";
		cin >> xc >> yc >> r;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Line Drawing");
	if (choice == 2) {
		glutMouseFunc(mouseFuncCircle);
		glutDisplayFunc(drawingCircle);
	}
	else {
		glutDisplayFunc(circleBres);
	}
	myInit();
	glutMainLoop();
}