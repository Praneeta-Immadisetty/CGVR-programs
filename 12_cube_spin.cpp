//#include <stdlib.h>
//#include <GL/glut.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <time.h>
//
//GLfloat vertices[] = { //unit cube vertices
//	-1.0,-1.0,-1.0,
//	1.0,-1.0,-1.0,
//	1.0,1.0,-1.0,
//	-1.0,1.0,-1.0,
//	-1.0,-1.0,1.0,
//	1.0,-1.0,1.0,
//	1.0,1.0,1.0,
//	-1.0,1.0,1.0
//};
//
//GLfloat colors[] = { 0.0,0.0,0.0, 1.0,0.0,0.0,
//1.0,1.0,0.0, 0.0,1.0,0.0, 0.0,0.0,1.0,
//1.0,0.0,1.0, 1.0,1.0,1.0, 0.0,1.0,1.0 }; //colors for each vertex
//
//GLubyte cubeIndices[] = {
//	0,3,2,1,
//	2,3,7,6,
//	0,4,7,3,
//	1,2,6,5,
//	4,5,6,7,
//	0,1,5,4
//};
//
//static GLfloat theta[] = { 0.0,0.0,0.0 };
//static GLfloat beta[] = { 0.0,0.0,0.0 };
//static GLint axis = 2;
//
//void displaySingle(void) {
//	/* display callback, clear frame buffer and z buffer,
//	   rotate cube and draw, swap buffers */
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glLoadIdentity();
//	glRotatef(theta[0], 1.0, 0.0, 0.0);
//	glRotatef(theta[1], 0.0, 1.0, 0.0);
//	glRotatef(theta[2], 0.0, 0.0, 1.0);
//
//	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);
//
//	glBegin(GL_LINES);
//	glVertex3f(0.0, 0.0, 0.0);
//	glVertex3f(1.0, 1.0, 1.0);
//	glEnd();
//
//	glFlush();
//}
//
//void spinCube() {
//	for (int i = 0; i < 10000000; i++);
//	theta[axis] += 2.0;
//	if (theta[axis] > 360.0) theta[axis] -= 360.0;
//	glutPostRedisplay();
//}
//
//void mouse(int btn, int state, int x, int y) {
//	/* mouse callback, selects an axis about which to rotate */
//	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
//	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
//	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
//}
//
//// Needed for completion of problem, but not vv imp
//// void myReshape(int w, int h) {
//// 	glViewport(0, 0, w, h);
//// 	glMatrixMode(GL_PROJECTION);
//// 	glLoadIdentity();
//// 	if (w <= h)
//// 		glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,
//// 			2.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
//// 	else
//// 		glOrtho(-2.0 * (GLfloat)w / (GLfloat)h,
//// 			2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, -10.0, 10.0);
//// 	glMatrixMode(GL_MODELVIEW);
//// }
//
//void myinit() {
//	glEnable(GL_DEPTH_TEST); /* Enable hidden--surface--removal */
//	glEnableClientState(GL_COLOR_ARRAY);
//	glEnableClientState(GL_VERTEX_ARRAY);
//	glVertexPointer(3, GL_FLOAT, 0, vertices);
//	glColorPointer(3, GL_FLOAT, 0, colors);
//	glColor3f(1.0, 1.0, 1.0);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(-500.0, 500.0, -500.0, 500.0, -500.0, 500.0);
//}
//
//int main(int argc, char** argv) {
//	//window 1
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(900, 900);
//	glutCreateWindow("colorcube");
//	// 	glutReshapeFunc(myReshape);
//	glutDisplayFunc(displaySingle);
//	glutIdleFunc(spinCube);
//	glutMouseFunc(mouse);
//	myinit();
//	glutMainLoop();
//	return 0;
//}

#include<windows.h>
#include<stdio.h>
#include<math.h>
#include<GL/glut.h>

GLfloat d = 0;
int a = 0;

void MyInit() {
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
}

void Spin() {
    d = d + 0.02;
    if (d > 360)
        d = 0;
    glutPostRedisplay();
}

void Face(GLfloat A[], GLfloat B[], GLfloat C[], GLfloat D[]) {
    glBegin(GL_POLYGON);
    glVertex3fv(A);
    glVertex3fv(B);
    glVertex3fv(C);
    glVertex3fv(D);
    glEnd();
}

void Cube(GLfloat V0[], GLfloat V1[], GLfloat V2[], GLfloat V3[], GLfloat V4[], GLfloat V5[], GLfloat V6[], GLfloat V7[]) {
    glColor3f(1, 0, 0);
    Face(V0, V1, V2, V3); //Front
    glColor3f(0, 1, 0);
    Face(V4, V5, V6, V7); //Back
    glColor3f(0, 0, 1);
    Face(V0, V4, V7, V3); //Left
    glColor3f(1, 1, 0);
    Face(V1, V5, V6, V2); //Right
    glColor3f(1, 0, 1);
    Face(V2, V3, V7, V6); //Bot
    glColor3f(0, 1, 1);
    Face(V0, V1, V5, V4); //Top
}

void Draw() {
    GLfloat V[8][3] = {
                            {-0.5, 0.5, 0.5},
                            { 0.5, 0.5, 0.5},
                            { 0.5,-0.5, 0.5},
                            {-0.5,-0.5, 0.5},
                            {-0.5, 0.5,-0.5},
                            { 0.5, 0.5,-0.5},
                            { 0.5,-0.5,-0.5},
                            {-0.5,-0.5,-0.5},
    };
    GLfloat rV[8][3], r;
    int i;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    r = d * 3.14 / 180;
    if (a == 1){
        for (i = 0; i < 8; i++) {
            rV[i][0] = V[i][0];
            rV[i][1] = V[i][1] * cos(r) - V[i][2] * sin(r);
            rV[i][2] = V[i][1] * sin(r) + V[i][2] * cos(r);
        }
    }
    if (a == 2) {
        for (i = 0; i < 8; i++) {
            rV[i][0] = V[i][2] * sin(r) + V[i][0] * cos(r);
            rV[i][1] = V[i][1];
            rV[i][2] = V[i][2] * cos(r) - V[i][0] * sin(r);
        }
    }
    if (a == 3) {
        for (i = 0; i < 8; i++) {
            rV[i][0] = V[i][0] * cos(r) - V[i][1] * sin(r);
            rV[i][1] = V[i][0] * sin(r) + V[i][1] * cos(r);
            rV[i][2] = V[i][2];
        }
    }
    Cube(rV[0], rV[1], rV[2], rV[3], rV[4], rV[5], rV[6], rV[7]);
    glutSwapBuffers();
}

void mouse(int btn, int state, int x, int y) {
	/* mouse callback, selects an axis about which to rotate */
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) a = 1;
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) a = 2;
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) a = 3;
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(50, 150);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Cube Spin with Matrices");
    MyInit();
    glutDisplayFunc(Draw);
    glutIdleFunc(Spin);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

