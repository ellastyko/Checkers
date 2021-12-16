#pragma once
#include "checker.h"

class board
{
	checker* checkers;
	int Presence;
	float x1, x2, x3, x4, y1, y2, y3, y4, xCenter, yCenter;
	board *LWhite, *RWhite, *LBlack, *RBlack;
public:
	void CELL();
	checker* GET_Checker();
	int GET_Presence();
	board* GETL_White();
	board* GETR_White();
	board* GETL_Black();
	board* GETR_Black();
	float GETX();
	float GETY();
	void SETLW(board*);
	void SETRW(board*);
	void SETLB(board*);
	void SETRB(board*);
	void SET_Checkers(checker*);
	void SET_Presence(int presence);
	board(int checking, float X1, float X2, float X3, float X4, float Y1, float Y2, float Y3, float Y4, float xC, float yC, int presence);
	void DeleteChecker();
};

