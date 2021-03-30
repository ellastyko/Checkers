#include <gl/glut.h>									
#include "checker.h"
#include "logic.h"	
#define _CRT_SECURE_NO_WARNINGS
logic* log;
int we, he;
void display() { log->display(); }

void mouse(int button, int state, int x, int y) { log->mouse(button, state, x, y); }

void motion_of_mouse(int x, int y) { log->motion_of_mouse(x, y); }

void timer(int value) {
	log->timer(value);
	glutTimerFunc(500, timer, 0);
}

void keyboard(int key, int x, int y) { log->keyboard(key, x, y); }

void changeSize(int w, int h) { log->setter(w, h); }

void keyboard2(unsigned char key, int x, int y) { log->keyboard2( key,  x,  y); }


int main(int argc, char** argv) {
	logic scene(800, 600);
	log = &scene;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(654, 600);
	glutCreateWindow("Russian Checkers");
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion_of_mouse);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(keyboard2);
	glutSpecialFunc(keyboard);
	glutTimerFunc(100, timer, 0);
	glutMainLoop();
}