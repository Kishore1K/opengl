#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <GL/glut.h>
#define BLACK 0, 0, 0
double cameraAngle;
double cameraAngleDelta;
double cameraHeight;
double cameraRadius;
double rectAngle;
bool canDrawGrid;
GLUquadric* quad;
void swap(int& a, int& b)
{
	int t = a;
	a = b;
	b = t;
}
void chair(double x, double y, int r1, int r2, int r3, int r4)
{
	double equ[4];
	equ[0] = 0;	
	equ[1] = 0;	
	equ[2] = 1;
	equ[3] = -16;
	glClipPlane(GL_CLIP_PLANE0, equ);
	glEnable(GL_CLIP_PLANE0);
	{
		glColor3f(1, 0, 0);
		glPushMatrix();
		{
			glTranslatef(x, y, 10);
			glutSolidCube(20);
		}glPopMatrix();

	}glDisable(GL_CLIP_PLANE0);
	int j, i;
	int dx[4] = { 1,1,-1,-1 };
	int dy[4] = { -1,1,-1,1 };
	int rise[4] = { r1,r2,r3,r4 };
	for (i = 0; i < 4; i++)
	{
		for (j = 14; j >= 2; j -= 4)
		{
			glColor3f(0, 1, 1);
			glPushMatrix();
			{
				glTranslatef(x + 7 * dx[i], y + 7 * dy[i], j);
				glutSolidCube(4);
			}glPopMatrix();
		}
		if (rise[i])
			for (j = 38; j >= 14; j -= 4)
			{
				glColor3f(0, 1, 1);
				glPushMatrix();
				{
					glTranslatef(x + 7 * dx[i], y + 7 * dy[i], j);
					glutSolidCube(4);
				}glPopMatrix();

			}
	}
	int x1, x2;
	int y1, y2;
	for (i = 0; i < 4; i++)
		for (j = i + 1; j < 4; j++)
		{
			if (rise[i] && rise[j])
			{
				x1 = x + 7 * dx[i];
				x2 = x + 7 * dx[j];
				y1 = y + 7 * dy[i];
				y2 = y + 7 * dy[j];
				goto last;
			}
		}
last:
	if (x1 > x2) swap(x1, x2);
	if (y1 > y2) swap(y1, y2);
	for (j = 38; j >= 15; j -= 7)
	{
		for (x = x1; x <= x2; x += 3)
			for (y = y1; y <= y2; y += 3)
			{
				glColor3f(1, 0, 1);
				glPushMatrix();
				{
					glTranslatef(x, y, j);
					glutSolidCube(3);
				}glPopMatrix();
			}
	}
}
void shelf()
{
	int i, j;
	double equ[4];
	equ[0] = 0;
	equ[1] = 0;	
	equ[2] = 1;
	for (i = -40; i <= 40; i += 20)
	{
		glColor3f(1, 0, 0);
		glPushMatrix();
		{
			glTranslatef(90, i, 10);
			glutSolidCube(20);
		}glPopMatrix();
		for (j = 30; j <= 70; j += 20)
		{
			equ[3] = -j - 7;
			glClipPlane(GL_CLIP_PLANE0, equ);
			glEnable(GL_CLIP_PLANE0);
			{
				glColor3f(0, 0.3, 0.8);	//blue
				glPushMatrix();
				{
					glTranslatef(90, i, j);
					glutSolidCube(20);
				}
				glPopMatrix();
			}
			glDisable(GL_CLIP_PLANE0);
		}
	}
	equ[0] = 1;
	equ[1] = 0;
	equ[2] = 0;
	equ[3] = -100;
	glClipPlane(GL_CLIP_PLANE0, equ);
	glEnable(GL_CLIP_PLANE0);
	{
		glColor3f(0, 0.7, 0.8);	
		glPushMatrix();
		{
			glTranslatef(52, 0, 50);
			glutSolidCube(100);
		}
		glPopMatrix();
	}
	glDisable(GL_CLIP_PLANE0);
	for (i = 20; i <= 80; i += 3)
	{
		glColor3f(0, 0.7, 0.8);	//blue
		glPushMatrix();
		{
			glTranslatef(82, -48, i);
			glutSolidCube(3);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(82, 48, i);
			glutSolidCube(3);
		}
		glPopMatrix();
	}
}
void table()
{
	glColor3f(0, 0, 0);
	glPushMatrix();
	{
		glScaled(1.25, 1.65, 1);
		glTranslatef(0, 0, 30);
		gluDisk(quad, 28, 30, 18, 1);
	}
	glPopMatrix();
	glColor3f(1, .5, 0);
	glPushMatrix();
	{
		glScaled(1.25, 1.65, 1);
		glTranslatef(0, 0, 30);
		gluDisk(quad, 0, 28, 18, 1);
	}
	glPopMatrix();
	glColor3f(.2, .5, .9);
	int i;
	int dx[4] = { 20,20,-20,-20 };
	int dy[4] = { -20,20,-20,20 };
	for (i = 0; i < 4; i++)
	{
		glPushMatrix();
		{
			glTranslatef(dx[i], dy[i], 0);
			gluCylinder(quad, 4, 4, 30, 18, 1);
		}
		glPopMatrix();
	}
	glColor3f(.3, .3, .3);
	for (i = -20; i <= 20; i += 4)
	{
		glPushMatrix();
		{
			glTranslatef(i, 20, 20);
			glutSolidCube(4);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(0, i, 20);
			glutSolidCube(4);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(i, -20, 20);
			glutSolidCube(4);
		}
		glPopMatrix();
	}
}
void chandelier()
{
	glColor3f(1, .5, .2);
	glPushMatrix();
	{
		glTranslatef(0, 0, 85);
		glScaled(1, 1, 200);
		gluDisk(quad, 0, 20, 18, 1);
	}
	glPopMatrix();
	glColor3f(1, .5, .2);
	glPushMatrix();
	{
		glTranslatef(0, 0, 110);
		glScaled(1, 1, 200);
		gluDisk(quad, 0, 30, 18, 1);
	}
	glPopMatrix();
	glColor3f(.3, .5, .6);
	glPushMatrix();
	{
		glTranslatef(0, 0, 110);
		gluCylinder(quad, 1, 2, 30, 18, 1);
	}
	glPopMatrix();
	glColor3f(.2, .5, .9);
	int i, j;
	int dx[4] = { 2,2,-2,-2 };
	int dy[4] = { -2,2,-2,2 };
	int dx1[8] = { 0,0,10,10,-10,-10,18,-18 };
	int dy1[8] = { 18,-18,-13,13,13,-13,0,0 };
	for (i = 0; i < 4; i++)
	{
		glPushMatrix();
		{
			glTranslatef(dx[i], dy[i], 85);
			gluCylinder(quad, 2, 2, 30, 18, 1);
		}
		glPopMatrix();
	}
	int c[3];
	for (i = 0; i < 8; i++)
	{
		glColor3f(1, 1, 1);
		glPushMatrix();
		{
			glTranslatef(dx1[i], dy1[i], 85);
			gluCylinder(quad, 2, 2, 25, 18, 1);
		}
		glPopMatrix();
		glColor3f(.7, .6, .9);
		glPushMatrix();
		{
			glTranslatef(dx1[i], dy1[i], 110);
			gluCylinder(quad, 2, 2, 5, 18, 1);
		}
		glPopMatrix();
		glColor3f(1, 0, 0);
		glPushMatrix();
		{
			glTranslatef(dx1[i], dy1[i], 117);
			glutSolidSphere(2, 2, 2);
		}
		glPopMatrix();
		c[0] = c[1] = c[2] = 0;
		for (j = 111; j >= 70; j -= 4)
		{
			c[(j + 1) % 3] = 1;
			glColor3f(c[0], c[1], c[2]);
			glPushMatrix();
			{
				glTranslatef(1.6 * dx1[i], 1.6 * dy1[i], j);
				glutSolidSphere(1, 4, 4);
			}
			glPopMatrix();
			c[(j + 1) % 3] = 0;
		}
	}
}
void window()
{
	int i, j, z, j1;
	int x[4] = { -100,-100,-120,-120 };
	int y[4] = { 30,-30,50,-50 };
	glColor3f(.6, .6, .1);
	for (i = 0; i < 4; i++)
	{
		glPushMatrix();
		{
			glTranslatef(x[i], y[i], 50);
			gluCylinder(quad, 2, 2, 50, 18, 1);
		}
		glPopMatrix();
	}
	for (i = -30; i <= 30; i += 4)
	{
		glPushMatrix();
		{
			glTranslatef(-100, i, 50);
			glutSolidCube(4);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(-100, i, 100);
			glutSolidCube(4);
		}
		glPopMatrix();
	}
	glColor3f(1, 1, 1);
	for (i = -100, j = 30, j1 = -30; i >= -120; i -= 4, j += 4, j1 -= 4)
	{
		for (z = 50; z <= 100; z += 25)
		{
			glPushMatrix();
			{
				glTranslatef(i, j, z);
				glutSolidCube(4);
			}
			glPopMatrix();
		}
		for (z = 50; z <= 100; z += 25)
		{
			glPushMatrix();
			{
				glTranslatef(i, j1, z);
				glutSolidCube(4);
			}
			glPopMatrix();
		}
	}
	z = 75;
	i += 4, j -= 5, j1 += 5;
	glColor3f(0, 0, 0);
	glPushMatrix();
	{
		glTranslatef(i, j, z);
		glutSolidSphere(2, 5, 5);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(i, j1, z);
		glutSolidSphere(2, 5, 5);
	}
	glPopMatrix();
}
bool st;
double H;
double segs = 30;
double min(double a, double b)
{
	if (a < b) return a;
	else return b;

}
double max(double a, double b)
{
	if (a > b) return a;
	else return b;
}
void screen()
{
	int i, j;
	glColor3f(1, 1, 1);
	for (i = -30; i <= 30; i += 4)
	{
		glPushMatrix();
		{
			glTranslatef(-95, i, 100);
			glutSolidCube(4);
		}
		glPopMatrix();
	}
	if (st == 0) H = min(1.02 * H, 60);
	else H = max(10, 0.98 * H);
	double h = H / segs;
	double now = -30, now1;
	double cl = 1;
	double x[4], y[4], z[4];
	z[0] = 100;
	z[1] = 100;
	z[2] = 50;
	z[3] = 50;
	for (i = 1; i < segs; i++)
	{
		now1 = now + h;
		if (i % 2)
		{
			x[0] = -90;
			y[0] = now;
			x[1] = -100;
			y[1] = now1;
			x[2] = -100;
			y[2] = now1;
			x[3] = -90;
			y[3] = now;
		}
		else
		{
			x[0] = -100;
			y[0] = now;
			x[1] = -90;
			y[1] = now1;
			x[2] = -90;
			y[2] = now1;
			x[3] = -100;
			y[3] = now;
		}
		glColor3f(0, 0, cl);
		glPushMatrix();
		{
			glBegin(GL_QUADS);
			{
				for (j = 0; j < 4; j++)
					glVertex3f(x[j], y[j], z[j]);
			}
			glEnd();
		}
		glPopMatrix();
		now = now1;
		cl *= .95;
	}
}
void plate(double X, double Y, double Z, double r1, double r2, double h)
{
	glColor3f(0, .2, .2);
	glPushMatrix();
	{
		glTranslatef(X, Y, Z);
		gluCylinder(quad, r1, r1 + (r2 - r1) / 2, h / 2, 13, 13);
	}
	glPopMatrix();
	glColor3f(0, 0, 1);
	glPushMatrix();
	{
		glTranslatef(X, Y, Z + h / 2);
		gluCylinder(quad, r1 + (r2 - r1) / 2, r2 + (r2 - r1) / 2, h / 2, 13, 13);
	}
	glPopMatrix();
	glColor3f(1, 1, 1);
	glPushMatrix();
	{
		glScaled(1, 1, 1);
		glTranslatef(X, Y, Z + .2);
		gluDisk(quad, 0, r1, 18, 1);
	}
	glPopMatrix();
}
void glass(double X, double Y, double Z, double r1, double r2, double h)
{
	plate(X, Y, Z, r1, r2, h);

	glColor3f(1, 1, 1);
	glPushMatrix();
	{
		glTranslatef(X, Y, Z + h);
		gluCylinder(quad, r1, r2, 2, 13, 13);
	}
	glPopMatrix();
}
void bottle(double X, double Y, double Z)
{
	glColor3f(.4, 1, .2);
	glPushMatrix();
	{
		glTranslatef(X, Y, Z);
		gluCylinder(quad, 2, 3, 2, 13, 13);
	}
	glPopMatrix();
	Z += 2;
	glColor3f(1, 1, .6);
	glPushMatrix();
	{
		glTranslatef(X, Y, Z);
		gluCylinder(quad, 3, 3, 4, 13, 13);
	}
	glPopMatrix();
	Z += 4;
	glColor3f(.4, .9, .9);
	glPushMatrix();
	{
		glTranslatef(X, Y, Z);
		gluCylinder(quad, 3, 1.2, 3, 13, 13);
	}
	glPopMatrix();
	Z += 3;
	glColor3f(.4, 1, 1);
	glPushMatrix();
	{
		glTranslatef(X, Y, Z);
		gluCylinder(quad, 1.2, 1.2, 3, 13, 13);
	}
	glPopMatrix();
	Z += 3;
	glColor3f(0, 0, 0);
	glPushMatrix();
	{
		glTranslatef(X, Y, Z);
		gluCylinder(quad, 1.2, 1.2, 2, 13, 13);
	}
	glPopMatrix();
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(BLACK, 0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraRadius * cos(cameraAngle), cameraRadius * sin(cameraAngle), cameraHeight, 0, 0, 0, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	{
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		{
			glVertex3f(-100, -100, 0);
			glVertex3f(-100, 100, 0);
			glVertex3f(100, 100, 0);
			glVertex3f(100, -100, 0);
		}glEnd();
	}glPopMatrix();	
	int i;
	glColor3f(0.3, 0.3, 0.3);
	if (canDrawGrid == true)
	{
		glBegin(GL_LINES);
		{
			for (i = -10; i <= 10; i++)
			{

				if (i == 0)
					continue;	
				glVertex3f(i * 10, -100, 0);
				glVertex3f(i * 10, 100, 0);
				glVertex3f(-100, i * 10, 0);
				glVertex3f(100, i * 10, 0);
			}
		}glEnd();
	}
	chair(0, 60, 0, 1, 0, 1);
	chair(0, -60, 1, 0, 1, 0);
	chair(-45, 30, 0, 0, 1, 1);
	chair(-45, -30, 0, 0, 1, 1);
	chair(45, 30, 1, 1, 0, 0);
	chair(45, -30, 1, 1, 0, 0);
	shelf();
	table();
	chandelier();
	window();
	screen();
	plate(20, 20, 30, 5, 10, 4);
	plate(-20, 20, 30, 5, 10, 4);
	plate(-20, -20, 30, 5, 10, 4);
	plate(20, -20, 30, 5, 10, 4);
	glass(0, 0, 30, 3, 3, 8);
	glass(6, 1, 30, 3, 3, 8);
	bottle(0, 40, 30);
	glutSwapBuffers();
}
void animate() {
	
	cameraAngle += cameraAngleDelta;
	rectAngle -= 1;
	glutPostRedisplay();
}
void keyboardListener(unsigned char key, int x, int y) {
	switch (key) {
	case '1':
		cameraAngleDelta = -cameraAngleDelta;
		break;
	case '2':
		cameraAngleDelta *= 1.1;
		break;
	case '3':	
		cameraAngleDelta /= 1.1;
		break;
	case '8':
		canDrawGrid = !canDrawGrid;
		break;
	case 'a':	
		st = !st;
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}
void specialKeyListener(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_DOWN:	
		cameraRadius += 10;
		break;
	case GLUT_KEY_UP:
		if (cameraRadius > 10)
			cameraRadius -= 10;
		break;
	case GLUT_KEY_RIGHT:
		break;
	case GLUT_KEY_LEFT:
		break;

	case GLUT_KEY_PAGE_UP:
		cameraHeight += 10;
		break;
	case GLUT_KEY_PAGE_DOWN:
		cameraHeight -= 10;
		break;

	case GLUT_KEY_INSERT:
		break;

	case GLUT_KEY_HOME:
		break;
	case GLUT_KEY_END:
		break;

	default:
		break;
	}
}
void mouseListener(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {		
			cameraAngleDelta = -cameraAngleDelta;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		break;

	case GLUT_MIDDLE_BUTTON:
		break;
	default:
		break;
	}
}


void init() {
	cameraAngle = 0;	
	cameraAngleDelta = 0.002;
	rectAngle = 0;
	canDrawGrid = true;
	cameraHeight = 150;
	cameraRadius = 150;
	glClearColor(BLACK, 0);
	quad = gluNewQuadric();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 1, 0.1, 10000.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("My OpenGL Program");
	init();
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display);	
	glutIdleFunc(animate);		
	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);
	glutMainLoop();	
	return 0;
}
