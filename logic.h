#pragma once
#include "checker.h"
#include "board.h"
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS

class logic
{
	board* cell, *Acell;
	checker* Achecker;	
	int rotate_x = -50, rotate_z = 0, step = 1, White, Black;
	char END_STRING[20], PLAY_STRING[80], BELOW_STRING1[30], STAT_STRING1[30], STAT_STRING2[30], BELOW_STRING2[30], STAT_STRING3[30], PAUSE[10];
public:
	int start = 0, stata = -1, level = 1, setUp = 0, t = 10, pause = -1;
	int button, tick, time, move = -1, k1, k2, h, w;
	float wins, loses;
	int gamecount;
	double mouseX, mouseZ;
	float rate, ratio;
	void StartAgain();
	logic(int,int);
	board* GET_CELL();
	void display();
	void Board();
	void Relocation(board* FC, board* SC, int& step);
	bool Eating(board* FC, board* SC, int& step);
	bool AbleToEat(board*, int step);
	bool AbilityEat(board* cell, int step);
	bool findNearest(board* cell, int x, int y, int& ammount, int move);
	bool ToFindCell(board* cell, board* Acell, int x, int y, int& ammount, int step);
	bool TheFarestCell(board* cell, board* Acell, int x, int y, int& ammount, int step);
	void mouse(int button, int state, int x, int y);
	void motion_of_mouse(int x, int y);
	void keyboard(int key, int x, int y);
	void keyboard2(unsigned char key, int x, int y);
	void timer(int value);
	void win();
	void lose();
	void setter(int w, int h);
	int koordinates(int x, int y);
	void rating();
	void reseting(int j);
};
