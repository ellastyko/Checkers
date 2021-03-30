#include "checker.h"
#include <gl/glut.h>	
#include <cmath>

checker::checker(double xCenter, double yCenter, int col) {
	x = xCenter;
	y = yCenter;
	color = col;
	dame = 0;
}

void checker::SET_X(double xCenter) { x = xCenter; }
void checker::SET_Y(double yCenter) { y = yCenter; }
void checker::SET_DAME(bool d) { dame = d; }
double checker::GET_X() { return x; }
double checker::GET_Y() { return y; }
int checker::GET_Color() { return color; }
bool checker::GET_DAME() { return dame; }

void cylinder(GLfloat radius, GLfloat height, float r, float g, float b, int z)
{
	glColor3f(r, g, b);
	GLfloat x = 0.0;
	GLfloat y = 0.0;
	GLfloat angle = 0.0;
	GLfloat angle_stepsize = 0.1;
	glBegin(GL_QUAD_STRIP);
	angle = 0.0;
	while (angle < 2 * 3.14) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		glVertex3f(x, y, 0.0);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glVertex3f(radius, 0.0, 0.0);
	glEnd();
	if (z == 0) {

		glBegin(GL_POLYGON);
		angle = 0.0;
		while (angle < 2 * 3.14) {
			x = radius * cos(angle);
			y = radius * sin(angle);
			glVertex3f(x, y, height);
			angle = angle + angle_stepsize;
		}
		glVertex3f(radius, 0.0, height);
		glEnd();
	}
}

void checker::Checker()
{
	glPushMatrix();
	glTranslated(x, y, 0.0);
	if (dame)
	{
		if (this->color == 0) {
			cylinder(0.08, 0.025, 0.82, 0.82, 0.82, 0);
			cylinder(0.0799, 0.026, 0.9, 0.9, 0.9, 0);
			cylinder(0.03, 0.05, 0.8, 0.8, 0.0, 1);
		}
		else {
			cylinder(0.08, 0.025, 0.15, 0.15, 0.15, 0);
			cylinder(0.0799, 0.026, 0.1, 0.1, 0.1, 0);
			cylinder(0.03, 0.05, 0.8, 0.8, 0.0, 1);
		}
	}
	else {
		if (this->color == 0) {
			cylinder(0.08, 0.025, 0.82, 0.82, 0.82, 0);
			cylinder(0.0799, 0.026, 0.9, 0.9, 0.9, 0);
		}
		else {
			cylinder(0.08, 0.025, 0.15, 0.15, 0.15, 0);
			cylinder(0.0799, 0.026, 0.1, 0.1, 0.1, 0);
		}
	}
	glPopMatrix();
	glColor3f(0.0, 0.0, 0.0);
}


