#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gl/glut.h>
#define M_PI 3.14159265358979323846
void sphere()
{
	double c = M_PI / 180, phi, phir, phir20, theta, thetar, x, y, z,
		c80;
	for (phi = -80.0; phi <= 80.0; phi += 10.0)
	{
		phir = c * phi;
		phir20 = c * (phi + 10);
		glBegin(GL_QUAD_STRIP);
		for (theta = -180.0; theta <= 180.0; theta += 10.0)
		{
			thetar = c * theta;
			x = sin(thetar) * cos(phir);
			y = cos(thetar) * cos(phir);
			z = sin(phir);
			glVertex3d(x, y, z);
			x = sin(thetar) * cos(phir20);
			y = cos(thetar) * cos(phir20);
			z = sin(phir20);
			glVertex3d(x, y, z);
		}
		glEnd();
	}
	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(0.0, 0.0, 1.0);
	c80 = c * 80.0;
	z = sin(c80);
	for (theta = -180.0; theta <= 180.0; theta += 10.0)
	{
		thetar = c * theta;
		x = sin(thetar) * cos(c80);
		y = cos(thetar) * cos(c80);
		glVertex3d(x, y, z);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(0.0, 0.0, -1.0);
	c80 = c * 80.0;
	z = -sin(c80);
	for (theta = -180.0; theta <= 180.0; theta += 10.0)
	{
		thetar = c * theta;
		x = sin(thetar) * cos(c80);
		y = cos(thetar) * cos(c80);
		glVertex3d(x, y, z);
	}
	glEnd();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef(0.0, 0.0, -1);
	//glRotatef(45.0, 1.0, 1.0, 1.0);
	glTranslatef(0.0, 0.0, -1);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	sphere();
	glFlush();
}
void myInit()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glPointSize(1.0);
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Sphere Approximation");
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	myInit();
	glutMainLoop();
}