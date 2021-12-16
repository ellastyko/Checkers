#include "board.h"
#include <gl/glut.h>	

board* board::GETL_White() { return LWhite; }

board* board::GETR_White() { return RWhite; }

board* board::GETL_Black() { return LBlack; }

board* board::GETR_Black() { return RBlack; }

float board::GETX() { return xCenter; }

float board::GETY() { return yCenter; }

checker* board::GET_Checker() { return checkers; }

int board::GET_Presence() { return Presence; }

void board::SETLW(board* LW ) { this->LWhite = LW; }

void board::SETRW(board* RW) { this->RWhite = RW; }

void board::SETLB(board* LB) { this->LBlack = LB; }

void board::SETRB(board* RB) { this->RBlack = RB; }

void board::SET_Checkers(checker* che) { checkers = che; }

void board::SET_Presence(int presence) { Presence = presence; }

board::board(int checking, float X1, float X2, float X3, float X4, float Y1, float Y2, float Y3, float Y4, float xC, float yC, int presence) 
{
	checkers = NULL;
	x1 = X1;  y1 = Y1;
	x2 = X2;  y2 = Y2;
	x3 = X3;  y3 = Y3;
	x4 = X4;  y4 = Y4;
	xCenter = xC;
	yCenter = yC;
	Presence = presence;
	if(presence==1)
	   checkers = new checker(xCenter, yCenter, checking);
}

void  board::CELL() {
	
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(x1, y2, 0.0011);
	glVertex3f(x2, y2, 0.0011);
	glVertex3f(x3, y3, 0.0011);
	glVertex3f(x4, y4, 0.0011);
	glEnd();
	if (Presence == 1) { (*checkers).Checker(); }
}

void board::DeleteChecker() {
	delete[]checkers;
	Presence = 0;
}
