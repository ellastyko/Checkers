#include "logic.h"
#include <gl/glut.h>	
#include <iostream>
#include <fstream>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;


void logic::setter(int w, int h)
{	
	this->w = w;
	this->h = h;
	if (h == 0)
		h = 1;
	ratio = w * 1.0 / h;
}

board* logic::GET_CELL() { return cell; }

logic::logic(int w, int h) { StartAgain(); }

void logic::keyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP: rotate_x -= 5; break;
	case GLUT_KEY_DOWN: rotate_x += 5; break;
	case GLUT_KEY_RIGHT: rotate_z += 5; break;
	case GLUT_KEY_LEFT: rotate_z -= 5; break;
	case GLUT_KEY_F1:  start = 1;  break;
	case GLUT_KEY_F2: start = 0; StartAgain(); break;
	case GLUT_KEY_F3: stata *= -1; break;
	case GLUT_KEY_F4:
		if (start == 1) {
			break;
		}
		else {
			level *= -1;  
			if (level == 1) {
				time = 10;
			}
			else {
				time = 5;
			}
			break;
		}		
	case GLUT_KEY_F5: setUp++; reseting(-1); break;
	case GLUT_KEY_F6: pause *= -1; break;
	}
}

void logic::motion_of_mouse(int z, int x) {
	if (button == 1) {
		rotate_x += x - mouseX;
		rotate_z += z - mouseZ;
		mouseX = x;
		mouseZ = z;
	}
}

void logic::mouse(int button, int state, int z, int x) {

	int nummer, j;
	mouseX = x; mouseZ = z;
	if (start == 1) {
		if ((button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN)) {

			if (White == 0 || Black == 0) { return; }
			this->button = -1;
			if (Acell != NULL && TheFarestCell(GET_CELL(), Acell, z, x, nummer, step) && AbleToEat(Acell, step)) {
				if (Eating(Acell, &GET_CELL()[nummer], step)) {
					Acell = NULL;
					Achecker = NULL;
					return;
				}
			}
			if (Acell != NULL && ToFindCell(GET_CELL(), Acell, z, x, nummer, step) && !AbleToEat(Acell, step)) {
				Relocation(Acell, &GET_CELL()[nummer], step);
				Acell = NULL;
				Achecker = NULL;
				return;
			}
			if (findNearest(GET_CELL(), z, x, nummer, step)) {
				if (AbilityEat(GET_CELL(), step)) {
					if (AbleToEat(&GET_CELL()[nummer], step)) {
						Acell = &GET_CELL()[nummer];
						Achecker = GET_CELL()[nummer].GET_Checker();
						return;
					}
				}
				if (!AbilityEat(GET_CELL(), step)) {
					Acell = &GET_CELL()[nummer];
					Achecker = GET_CELL()[nummer].GET_Checker();
				}
			}
			return;
		}
	}
	if (start == 0 && setUp == 1)
	{
		if ((button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN)) {
			j = koordinates(z, x);
			if (j > 11 && j < 20)
				return;
			reseting(j);
		}
	}
	if ((state == GLUT_UP)) {
		this->button = 0;
	}
	if ((button == GLUT_RIGHT_BUTTON) & (state == GLUT_DOWN)) {
		this->button = 1;
		return;
	}
}

void Text(void* pointer, const char* p, float x, float y) {
	if (!p) { return; }
	glRasterPos2f(x, y);
	while (*p) {
		glutBitmapCharacter(pointer, *p);
		p++;
	}
}

void logic::keyboard2(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
	if (key == 32)
		pause *= -1;
}

void logic::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, w, h);  
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
	glOrtho(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (start == 0)
	{
		sprintf_s(PLAY_STRING, "Esc -  Exit             F1 - Start            F3 - Statistic: %d games", gamecount);
		if (level == 1) {
			sprintf_s(BELOW_STRING1, "F4 - EASY");
		}
		else {
			sprintf_s(BELOW_STRING1, "F4 - HARD");
		}
		if (stata == 1) {
			sprintf_s(STAT_STRING1, "Wins: %.0f", wins);
			sprintf_s(STAT_STRING2, "Loses: %.0f", loses);
			sprintf_s(STAT_STRING3, "Rate: %.1f", rate);
		}
		if (setUp == 0) {
			sprintf_s(BELOW_STRING2, "F5 - Replace checkers");
		}
		if (setUp == 1) {
			sprintf_s(PLAY_STRING, "Esc -  Exit             F2 - Menu           F3 - Statistic: %d games", gamecount);
			sprintf_s(BELOW_STRING2, "F5 - OK");
		}
	}
	else {
		if (White != 0 && Black != 0)
		{
			sprintf_s(PLAY_STRING, "Esc -  Exit             F2 - Menu             Time: %d sec.", time);
			if (level == 1)
			{
				sprintf_s(BELOW_STRING1, "EASY");
				t = 10;
			}
			else
			{
				sprintf_s(BELOW_STRING1, "HARD");
				t = 5;
			}
			if (pause == 1)
			{
				sprintf_s(PAUSE, "II PAUSE");
			}
		}
		else
		{
			sprintf_s(END_STRING, "Game Over!");
			sprintf_s(PLAY_STRING, "Esc -  Exit             F2 - Menu            F3 - Statistic: %d games", gamecount);
			sprintf_s(STAT_STRING1, "Wins: %.0f", wins);
			sprintf_s(STAT_STRING2, "Loses: %.0f", loses);
			sprintf_s(STAT_STRING3, "Rate: %.1f", rate);
			sprintf_s(END_STRING, "Game Over!");
		}
	}
	if (start == 0) 
	{
		Text(GLUT_BITMAP_TIMES_ROMAN_24, PLAY_STRING, 0.05f, 0.95f);
		if (level == 1) {
			Text(GLUT_BITMAP_TIMES_ROMAN_24, BELOW_STRING1, 0.4f, 0.17f);
		}
		else {
			Text(GLUT_BITMAP_TIMES_ROMAN_24, BELOW_STRING1, 0.4f, 0.17f);
		}
		if (stata == 1) {
			Text(GLUT_BITMAP_TIMES_ROMAN_24, STAT_STRING1, 0.845f, 0.88f);
			Text(GLUT_BITMAP_TIMES_ROMAN_24, STAT_STRING2, 0.845f, 0.81f);
			Text(GLUT_BITMAP_TIMES_ROMAN_24, STAT_STRING3, 0.845f, 0.74f);
		}
		if (setUp == 0) {
			Text(GLUT_BITMAP_TIMES_ROMAN_24, BELOW_STRING2, 0.32f, 0.09f);
		}
		if (setUp == 1) {
			Text(GLUT_BITMAP_TIMES_ROMAN_24, BELOW_STRING2, 0.42f, 0.09f);
		}
	}
	else
	{
		if (White != 0 && Black != 0)
		{
			Text(GLUT_BITMAP_TIMES_ROMAN_24, PLAY_STRING, 0.05f, 0.95f);
			if (level == 1)
			{
				Text(GLUT_BITMAP_TIMES_ROMAN_24, BELOW_STRING1, 0.45f, 0.17f);
			}
			else
			{
				Text(GLUT_BITMAP_TIMES_ROMAN_24, BELOW_STRING1, 0.45f, 0.17f);
			}
			if (pause == 1)
			{
				Text(GLUT_BITMAP_TIMES_ROMAN_24, PAUSE, 0.43f, 0.7f);
			}
		}
		else {
			Text(GLUT_BITMAP_TIMES_ROMAN_24, PLAY_STRING, 0.05f, 0.95f);
			Text(GLUT_BITMAP_TIMES_ROMAN_24, END_STRING, 0.4f, 0.7f);
			Text(GLUT_BITMAP_TIMES_ROMAN_24, STAT_STRING1, 0.845f, 0.88f);
			Text(GLUT_BITMAP_TIMES_ROMAN_24, STAT_STRING2, 0.845f, 0.81f);
			Text(GLUT_BITMAP_TIMES_ROMAN_24, STAT_STRING3, 0.845f, 0.74f);
		}
	}
	glPopMatrix();
	
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, ratio, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -3.0f);
	glRotatef(rotate_x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotate_z, 0.0f, 0.0f, 1.0f);
	if (Black == 0) {
		if (k1 == 0) {
			win();
			k1++;
		}
	}
	if (White == 0) {
		if (k2 == 0) {
			lose();
			k2++;
		}
	}
	if (White == 0 || Black == 0)
		rating();
	glEnable(GL_DEPTH_TEST);
	Board();
	glFlush();
	glutSwapBuffers();
}

void logic::rating()
{
	if (loses != 0)
		rate = wins / loses;
	else
		rate = wins;
	ofstream inFile;
	inFile.open("Rate.txt");
	if (!inFile)
		cout << "Error";
	inFile << rate;
	inFile.close();
	ofstream fout("Rate.txt");
	fout << rate;
	fout.close();
}

void logic::reseting(int j = -1)
{
	if (start != 1) {
		if (setUp == 1)
		{		
			if (cell[j].GET_Presence() == 0)
				cell[j].SET_Presence(1);
			else
				cell[j].SET_Presence(0);		
		}
		if (setUp == 2)
		{
			int wh = 0, bl = 0;
			for (int i = 0; i < 32; i++)
			{
				if (cell[i].GET_Presence() == 1 && cell[i].GET_Checker()->GET_Color() == 0)
					wh += 1;
				if (cell[i].GET_Presence() == 1  && cell[i].GET_Checker()->GET_Color() == 1)
					bl += 1;
			}
			White = wh;
			Black = bl;
			start = 1;
		}
	}
}

int logic::koordinates(int x, int y)
{
	int viewport[4];
	int iMin = -1, jMin = -1;
	double mvMatrix[16], projMatrix[16];
	double minDist = 1000;
	double wx;
	double wy;
	double wz;
	for (int i = 0; i < 32; i++)
	{
		wx = cell[i].GETX();
		wy = cell[i].GETY();
		wz = 0.0;
		glGetIntegerv(GL_VIEWPORT, viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
		glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
		double dx, dy, dz;
		gluProject(wx, wy, wz, mvMatrix, projMatrix, viewport, &dx, &dy, &dz);
		dy = viewport[3] - dy - 1;
		double d = (x - dx) * (x - dx) + (y - dy) * (y - dy);
		if (d < minDist)
		{
			minDist = d;
			jMin = i;
		}
	}
	return jMin;
}

void logic::win()
{
	wins++;
	ofstream inFile;
	inFile.open("Wins.txt");
	if (!inFile)
		cout << "Error";
	inFile << wins;
	inFile.close();
	ofstream fout("Wins.txt");
	fout << wins;
	fout.close();
}

void logic::lose()
{
	loses++;
	ofstream inFile;
	inFile.open("Loses.txt");
	if (!inFile)
		cout << "Error";
	inFile << loses;
	inFile.close();
	ofstream fout("Loses.txt");
	fout << loses;
	fout.close();
}

void logic::timer(int value)
{
	if (start == 1) {
		tick++;
		if (tick >= 2)
		{
			if (White != 0 && Black != 0)
			{
				if(pause != 1)
				   time--;
				if (time == 0)
				{
					step *= -1;
					time = t;
				}
				if (move != step)
				{
					time = t;
				}
				move = step;
			}
			tick = 0;
		}
		display();
	}
}

void logic::Board() {
	glTranslatef(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-0.9, -0.9, 0.0);
	glVertex3f(0.9, -0.9, 0.0);
	glVertex3f(0.9, 0.9, 0.0);
	glVertex3f(-0.9, 0.9, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-0.9, 0.9, 0.0);
	glVertex3f(-0.9, -0.9, 0.0);
	glVertex3f(-0.9, -0.9, -0.05);
	glVertex3f(-0.9, 0.9, -0.05);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0.9, 0.9, 0.0);
	glVertex3f(-0.9, 0.9, 0.0);
	glVertex3f(-0.9, 0.9, -0.05);
	glVertex3f(0.9, 0.9, -0.05);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3d(0.9, -0.9, 0.0);
	glVertex3d(0.9, 0.9, 0.0);
	glVertex3d(0.9, 0.9, -0.05);
	glVertex3d(0.9, -0.9, -0.05);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3d(-0.0, -0.9, 0.0);
	glVertex3d(0.9, -0.9, 0.0);
	glVertex3d(0.9, -0.9, -0.05);
	glVertex3d(-0.9, -0.9, -0.05);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-0.9, -0.9, -0.05);
	glVertex3f(0.9, -0.9, -0.05);
	glVertex3f(0.9, 0.9, -0.05);
	glVertex3f(-0.9, 0.9, -0.05);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(-0.83, -0.83, 0.001);
	glVertex3f(0.83, -0.83, 0.001);
	glVertex3f(0.83, 0.83, 0.001);
	glVertex3f(-0.83, 0.83, 0.001);
	glEnd();
	for (int i = 0; i < 32; i++) { cell[i].CELL(); }
}

void logic::StartAgain()
{
	setUp = 0;
	pause = -1;
	Acell = NULL;
	Achecker = NULL;
	White = 12, Black = 12, step = 1;
	time = t; tick = 0, k1 = 0, k2 = 0;
	
	/////////////////////////////
	ifstream outFile;
	outFile.open("Games.txt");
	if (!outFile)
		cout << "Error";
	outFile >> gamecount;
	outFile.close();
	gamecount++;
	ofstream inFile;
	inFile.open("Games.txt");
	if (!inFile)
		cout << "Error";
	inFile << gamecount;
	inFile.close();
	ofstream fout("Games.txt");
	fout << gamecount;
	fout.close();
	/////////////////////////
	outFile.open("Wins.txt");
	if (!outFile)
		cout << "Error";
	outFile >> wins;
	outFile.close();
	////////////////////////
	ifstream OutFile;
	OutFile.open("Rate.txt");
	if (!OutFile)
		cout << "Error";
	OutFile >> rate;
	OutFile.close();
	////////////////////////
	ifstream OUTFile;
	OUTFile.open("Loses.txt");
	if (!OUTFile)
		cout << "Error";
	OUTFile >> loses;
	OUTFile.close();

	cell = new board[32]{
	board(0, -0.8f, -0.6f, -0.6f, -0.8f, -0.8f, -0.8f, -0.6f, -0.6f, -0.7f, -0.7f, 1),  board(0, -0.4f, -0.2f, -0.2f, -0.4f, -0.8f, -0.8f, -0.6f, -0.6f, -0.3f, -0.7f, 1),
	board(0, -0.0f, 0.2f, 0.2f, -0.0f, -0.8f, -0.8f, -0.6f, -0.6f, 0.1f, -0.7f, 1),     board(0, 0.4f, 0.6f, 0.6f, 0.4f, -0.8f, -0.8f, -0.6f, -0.6f, 0.5, -0.7f, 1),
	board(0, -0.6f, -0.4f, -0.4f, -0.6f, -0.6f, -0.6f, -0.4f, -0.4, -0.5, -0.5f, 1),    board(0,-0.2f, -0.0f, -0.0f, -0.2f, -0.6, -0.6, -0.4, -0.4, -0.1, -0.5f, 1),
	board(0, 0.2f, 0.4f, 0.4f, 0.2f, -0.6f, -0.6f, -0.4f, -0.4f, 0.3f, -0.5f, 1),       board(0, 0.6f, 0.8f, 0.8f, 0.6, -0.6f, -0.6f, -0.4f, -0.4f, 0.7f, -0.5f, 1),
	board(0, -0.8f, -0.6f, -0.6f, -0.8f, -0.4f, -0.4f, -0.2f, -0.2f, -0.7f, -0.3f, 1),  board(0, -0.4f, -0.2f, -0.2f, -0.4f, -0.4f, -0.4f, -0.2f, -0.2f, -0.3f ,-0.3, 1),
	board(0, -0.0f, 0.2f, 0.2f, -0.0f, -0.4f, -0.4f, -0.2f, -0.2f, 0.1f, -0.3f, 1),     board(0, 0.4f, 0.6f, 0.6f, 0.4f, -0.4f, -0.4f, -0.2f, -0.2f, 0.5f, -0.3f, 1),
	board(0, -0.6f, -0.4f, -0.4f, -0.6f, -0.2f, -0.2f, 0.0f, 0.0f, -0.5f, -0.1f, 0),    board(0,-0.2f, -0.0f, 0.0f, -0.2f, -0.2f, -0.2f, 0.0f, 0.0f, -0.1f, -0.1f, 0),
	board(0, 0.2f, 0.4f, 0.4f, 0.2f, -0.2f, -0.2f, 0.0f, 0.0f, 0.3f, -0.1f, 0),         board(0, 0.6f, 0.8f, 0.8f, 0.6f, -0.2f, -0.2, 0.0f, 0.0f, 0.7f, -0.1f, 0),
	board(0, -0.8f, -0.6f, -0.6f, -0.8f, 0.0f, 0.0f, 0.2f, 0.2f, -0.7f, 0.1f, 0),       board(0,-0.4f, -0.2, -0.2f, -0.4f, 0.0f, 0.0f, 0.2f, 0.2f, -0.3, 0.1f, 0),
	board(0, -0.0f, 0.2f, 0.2f, -0.0f, 0.0f, 0.0f, 0.2f, 0.2f, 0.1, 0.1f, 0),           board(0, 0.4f, 0.6f, 0.6f, 0.4f, 0.0f, 0.0f, 0.2f, 0.2f, 0.5f, 0.1f, 0),
	board(1, -0.6f, -0.4f, -0.4f, -0.6f, 0.2f, 0.2f, 0.4f, 0.4f, -0.5, 0.3f, 1),        board(1,-0.2f, -0.0f, -0.0f, -0.2f, 0.2f, 0.2f, 0.4f, 0.4f, -0.1f, 0.3f, 1),
	board(1, 0.2f, 0.4f, 0.4f, 0.2f, 0.2f, 0.2f, 0.4f, 0.4f, 0.3f, 0.3f, 1),            board(1,0.6f, 0.8f, 0.8f, 0.6f, 0.2f, 0.2f, 0.4f, 0.4f, 0.7f, 0.3f, 1),
	board(1,-0.8f, -0.6f, -0.6f, -0.8f, 0.4f, 0.4f, 0.6f, 0.6f, -0.7f, 0.5, 1),         board(1,-0.4f, -0.2f, -0.2f, -0.4f, 0.4f, 0.4f, 0.6f, 0.6f, -0.3f, 0.5, 1),
	board(1,-0.0f, 0.2f, 0.2, 0.0f, 0.4f, 0.4f, 0.6f, 0.6f, 0.1f, 0.5f, 1),             board(1, 0.4f, 0.6f, 0.6f, 0.4f, 0.4, 0.4f, 0.6f, 0.6f, 0.5f, 0.5f, 1),
	board(1,-0.6f, -0.4f, -0.4f, -0.6, 0.6f, 0.6f, 0.8f, 0.8f, -0.5f, 0.7f, 1),         board(1, -0.2f, -0.0f, -0.0f, -0.2f, 0.6f, 0.6f, 0.8f, 0.8f, -0.1f, 0.7f, 1),
	board(1, 0.2f, 0.4f, 0.4f, 0.2f, 0.6f, 0.6f, 0.8f, 0.8f, 0.3f, 0.7f, 1),            board(1, 0.6f, 0.8f, 0.8f, 0.6f, 0.6f, 0.6f, 0.8f, 0.8f, 0.7f, 0.7f, 1),
	};

	cell[0].SETLW(NULL);         cell[0].SETRW(&cell[4]);
	cell[0].SETLB(NULL);        cell[0].SETRB(NULL);
	cell[1].SETLW(&cell[4]);     cell[1].SETRW(&cell[5]);
	cell[1].SETLB(NULL);        cell[1].SETRB(NULL);
	cell[2].SETLW(&cell[5]);     cell[2].SETRW(&cell[6]);
	cell[2].SETLB(NULL);        cell[2].SETRB(NULL);
	cell[3].SETLW(&cell[6]);     cell[3].SETRW(&cell[7]);
	cell[3].SETLB(NULL);        cell[3].SETRB(NULL);
	cell[4].SETLW(&cell[8]);     cell[4].SETRW(&cell[9]);
	cell[4].SETLB(&cell[1]);    cell[4].SETRB(&cell[0]);
	cell[5].SETLW(&cell[9]);     cell[5].SETRW(&cell[10]);
	cell[5].SETLB(&cell[2]);    cell[5].SETRB(&cell[1]);
	cell[6].SETLW(&cell[10]);    cell[6].SETRW(&cell[11]);
	cell[6].SETLB(&cell[3]);    cell[6].SETRB(&cell[2]);
	cell[7].SETLW(&cell[11]);    cell[7].SETRW(NULL);
	cell[7].SETLB(NULL);        cell[7].SETRB(&cell[3]);
	cell[8].SETLW(NULL);         cell[8].SETRW(&cell[12]);
	cell[8].SETLB(&cell[4]);    cell[8].SETRB(NULL);
	cell[9].SETLW(&cell[12]);    cell[9].SETRW(&cell[13]);
	cell[9].SETLB(&cell[5]);    cell[9].SETRB(&cell[4]);
	cell[10].SETLW(&cell[13]);   cell[10].SETRW(&cell[14]);
	cell[10].SETLB(&cell[6]);   cell[10].SETRB(&cell[5]);
	cell[11].SETLW(&cell[14]);   cell[11].SETRW(&cell[15]);
	cell[11].SETLB(&cell[7]);   cell[11].SETRB(&cell[6]);
	cell[12].SETLW(&cell[16]);   cell[12].SETRW(&cell[17]);
	cell[12].SETLB(&cell[9]);   cell[12].SETRB(&cell[8]);
	cell[13].SETLW(&cell[17]);   cell[13].SETRW(&cell[18]);
	cell[13].SETLB(&cell[10]);  cell[13].SETRB(&cell[9]);
	cell[14].SETLW(&cell[18]);   cell[14].SETRW(&cell[19]);
	cell[14].SETLB(&cell[11]);  cell[14].SETRB(&cell[10]);
	cell[15].SETLW(&cell[19]);   cell[15].SETRW(NULL);
	cell[15].SETLB(NULL);       cell[15].SETRB(&cell[11]);
	cell[16].SETLW(NULL);        cell[16].SETRW(&cell[20]);
	cell[16].SETLB(&cell[12]);  cell[16].SETRB(NULL);
	cell[17].SETLW(&cell[20]);   cell[17].SETRW(&cell[21]);
	cell[17].SETLB(&cell[13]);  cell[17].SETRB(&cell[12]);
	cell[18].SETLW(&cell[21]);   cell[18].SETRW(&cell[22]);
	cell[18].SETLB(&cell[14]);  cell[18].SETRB(&cell[13]);
	cell[19].SETLW(&cell[22]);   cell[19].SETRW(&cell[23]);
	cell[19].SETLB(&cell[15]);  cell[19].SETRB(&cell[14]);
	cell[20].SETLW(&cell[24]);   cell[20].SETRW(&cell[25]);
	cell[20].SETLB(&cell[17]);  cell[20].SETRB(&cell[16]);
	cell[21].SETLW(&cell[25]);   cell[21].SETRW(&cell[26]);
	cell[21].SETLB(&cell[18]);  cell[21].SETRB(&cell[17]);
	cell[22].SETLW(&cell[26]);   cell[22].SETRW(&cell[27]);
	cell[22].SETLB(&cell[19]);  cell[22].SETRB(&cell[18]);
	cell[23].SETLW(&cell[27]);   cell[23].SETRW(NULL);
	cell[23].SETLB(NULL);       cell[23].SETRB(&cell[19]);
	cell[24].SETLW(NULL);        cell[24].SETRW(&cell[28]);
	cell[24].SETLB(&cell[20]);  cell[24].SETRB(NULL);
	cell[25].SETLW(&cell[28]);   cell[25].SETRW(&cell[29]);
	cell[25].SETLB(&cell[21]);  cell[25].SETRB(&cell[20]);
	cell[26].SETLW(&cell[29]);   cell[26].SETRW(&cell[30]);
	cell[26].SETLB(&cell[22]);  cell[26].SETRB(&cell[21]);
	cell[27].SETLW(&cell[30]);   cell[27].SETRW(&cell[31]);
	cell[27].SETLB(&cell[23]);  cell[27].SETRB(&cell[22]);
	cell[28].SETLW(NULL);        cell[28].SETRW(NULL);
	cell[28].SETLB(&cell[25]);  cell[28].SETRB(&cell[24]);
	cell[29].SETLW(NULL);        cell[29].SETRW(NULL);
	cell[29].SETLB(&cell[26]);  cell[29].SETRB(&cell[25]);
	cell[30].SETLW(NULL);        cell[30].SETRW(NULL);
	cell[30].SETLB(&cell[27]);  cell[30].SETRB(&cell[26]);
	cell[31].SETLW(NULL);        cell[31].SETRW(NULL);
	cell[31].SETLB(NULL);       cell[31].SETRB(&cell[27]);

}

void logic::Relocation(board* FC, board* SC, int& step) {
	if (step == 1) {
		SC->SET_Presence(1);
		SC->SET_Checkers(FC->GET_Checker());
		FC->SET_Presence(0);
		SC->GET_Checker()->SET_X(SC->GETX());
		SC->GET_Checker()->SET_Y(SC->GETY());
		FC->SET_Checkers(NULL);
	}
	else
	{
		SC->SET_Presence(1);
		SC->SET_Checkers(FC->GET_Checker());
		FC->SET_Presence(0);
		SC->GET_Checker()->SET_X(SC->GETX());
		SC->GET_Checker()->SET_Y(SC->GETY());
		FC->SET_Checkers(NULL);
	}

	if (SC->GET_Checker()->GET_Color() == 0 && (SC == &cell[31] || SC == &cell[30] || SC == &cell[29] || SC == &cell[28]))
		SC->GET_Checker()->SET_DAME(1);
	if (SC->GET_Checker()->GET_Color() == 1 && (SC == &cell[0] || SC == &cell[1] || SC == &cell[2] || SC == &cell[3]))
		SC->GET_Checker()->SET_DAME(1);

	step *= -1;
}

bool logic::Eating(board* FC, board* SC, int& step) {
	board* KilledBox = NULL;
	int c;
	(step == 1) ? c = 1 : c = 0;
	board* hCLW = FC, *hCRW = FC, *hCLB = FC, *hCRB = FC;
	if (FC->GET_Checker()->GET_DAME()) {
		while (1) {
			hCLW = hCLW->GETL_White();
			if (hCLW == NULL)
				break;
			if (hCLW->GET_Presence() && hCLW->GET_Checker()->GET_Color() == c)
				KilledBox = hCLW;
			if (hCLW == SC)
				goto M;
		}
		while (1) {
			hCRW = hCRW->GETR_White();
			if (hCRW == NULL)
				break;
			if (hCRW->GET_Presence() && hCRW->GET_Checker()->GET_Color() == c)
				KilledBox = hCRW;
			if (hCRW == SC)
				goto M;
		}
		while (1) {
			hCLB = hCLB->GETL_Black();
			if (hCLB == NULL)
				break;
			if (hCLB->GET_Presence() && hCLB->GET_Checker()->GET_Color() == c)
				KilledBox = hCLB;
			if (hCLB == SC)
				goto M;
		}
		while (1) {
			hCRB = hCRB->GETR_Black();
			if (hCRB == NULL)
				break;
			if (hCRB->GET_Presence() && hCRB->GET_Checker()->GET_Color() == c)
				KilledBox = hCRB;
			if (hCRB == SC)
				goto M;
		}
	}
	else {
		if (FC->GETL_White() != NULL && FC->GETL_White()->GETL_White() != NULL && FC->GETL_White()->GETL_White() == SC)
			KilledBox = FC->GETL_White();
		if (FC->GETR_White() != NULL && FC->GETR_White()->GETR_White() != NULL && FC->GETR_White()->GETR_White() == SC)
			KilledBox = FC->GETR_White();
		if (FC->GETL_Black() != NULL && FC->GETL_Black()->GETL_Black() != NULL && FC->GETL_Black()->GETL_Black() == SC)
			KilledBox = FC->GETL_Black();
		if (FC->GETR_Black() != NULL && FC->GETR_Black()->GETR_Black() != NULL && FC->GETR_Black()->GETR_Black() == SC)
			KilledBox = FC->GETR_Black();
	}
M:
	if (KilledBox == NULL) {
		return 0;
	}
	SC->SET_Presence(1);
	SC->SET_Checkers(FC->GET_Checker());
	FC->SET_Presence(0);
	KilledBox->DeleteChecker();
	SC->GET_Checker()->SET_X(SC->GETX());
	SC->GET_Checker()->SET_Y(SC->GETY());
	FC->SET_Checkers(NULL);
	KilledBox->SET_Checkers(NULL);
	if (c == 0)
		White--;
	if (c == 1)
		Black--;
	if (AbleToEat(SC, step)) { return 1; }
	if (SC->GET_Checker()->GET_Color() == 0 && (SC == &cell[31] || SC == &cell[30] || SC == &cell[29] || SC == &cell[28]))
		SC->GET_Checker()->SET_DAME(1);
	if (SC->GET_Checker()->GET_Color() == 1 && (SC == &cell[0] || SC == &cell[1] || SC == &cell[2] || SC == &cell[3]))
		SC->GET_Checker()->SET_DAME(1);
	step *= -1;
	return 1;
}

bool logic::AbleToEat(board* cell, int step) {
	int c;
	if (!cell->GET_Presence())
		return 0;
	(cell->GET_Checker()->GET_Color() == 0) ? c = 1 : c = 0;
	if (cell->GET_Checker()->GET_DAME()) {
		board* hCLW = cell, *hCRW = cell, *hCLB = cell, *hCRB = cell;
		while (1) {
			hCLW = hCLW->GETL_White();
			if (hCLW == NULL)
				break;
			if (hCLW->GET_Presence() && !hCLW->GET_Checker()->GET_Color() == c)
				break;
			if (hCLW->GET_Presence() && hCLW->GET_Checker()->GET_Color() == c)
				if (hCLW->GETL_White() != NULL && !hCLW->GETL_White()->GET_Presence())
					return 1;
		}
		while (1)
		{
			hCRW = hCRW->GETR_White();
			if (hCRW == NULL)
				break;
			if (hCRW->GET_Presence() && !hCRW->GET_Checker()->GET_Color() == c)
				break;
			if (hCRW->GET_Presence() && hCRW->GET_Checker()->GET_Color() == c)
				if (hCRW->GETR_White() != NULL && !hCRW->GETR_White()->GET_Presence())
					return 1;
		}
		while (1)
		{
			hCLB = hCLB->GETL_Black();
			if (hCLB == NULL)
				break;
			if (hCLB->GET_Presence() && !hCLB->GET_Checker()->GET_Color() == c)
				break;
			if (hCLB->GET_Presence() && hCLB->GET_Checker()->GET_Color() == c)
				if (hCLB->GETL_Black() != NULL && !hCLB->GETL_Black()->GET_Presence())
					return 1;
		}
		while (1)
		{
			hCRB = hCRB->GETR_Black();
			if (hCRB == NULL)
				break;
			if (hCRB->GET_Presence() && !hCRB->GET_Checker()->GET_Color() == c)
				break;
			if (hCRB->GET_Presence() && hCRB->GET_Checker()->GET_Color() == c)
				if (hCRB->GETR_Black() != NULL && !hCRB->GETR_Black()->GET_Presence())
					return 1;
		}
	}
	else
	{
		if (step == 1)
		{
			if (cell->GETL_White() != NULL)
			{
				if (cell->GETL_White()->GETL_White() != NULL)
				{
					if (cell->GETL_White()->GET_Presence() && cell->GETL_White()->GET_Checker()->GET_Color() == c && !cell->GETL_White()->GETL_White()->GET_Presence())
					{
						return 1;
					}
				}
			}
			if (cell->GETR_White() != NULL)
			{
				if (cell->GETR_White()->GETR_White() != NULL)
				{
					if (cell->GETR_White()->GET_Presence() && cell->GETR_White()->GET_Checker()->GET_Color() == c && !cell->GETR_White()->GETR_White()->GET_Presence())
					{
						return 1;
					}
				}
			}
		}
		else
		{
			if (cell->GETL_Black() != NULL)
			{
				if (cell->GETL_Black()->GETL_Black() != NULL)
				{
					if (cell->GETL_Black()->GET_Presence() && cell->GETL_Black()->GET_Checker()->GET_Color() == c && !cell->GETL_Black()->GETL_Black()->GET_Presence())
					{
						return 1;
					}
				}

			}
			if (cell->GETR_Black() != NULL)
			{
				if (cell->GETR_Black()->GETR_Black() != NULL)
				{
					if (cell->GETR_Black()->GET_Presence() && cell->GETR_Black()->GET_Checker()->GET_Color() == c && !cell->GETR_Black()->GETR_Black()->GET_Presence())
					{
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

bool logic::AbilityEat(board* cell, int step) {
	for (int i = 0; i < 32; i++)
	{
		if (!cell[i].GET_Presence())
			continue;
		if ((step == 1 && cell[i].GET_Checker()->GET_Color() == 1) || step == -1 && cell[i].GET_Checker()->GET_Color() == 0)
			continue;
		if (AbleToEat(&cell[i], step))
			return 1;
	}
	return 0;
}

bool logic::findNearest(board* cell, int x, int y, int& ammount, int step)
{
	int viewport[4];
	int iMin = -1, jMin = -1;
	double mvMatrix[16], projMatrix[16];
	double minDist = 1000;
	for (int i = 0; i < 32; i++) {
		double wx, wy, wz;
		if (cell[i].GET_Presence()) {
			wx = cell[i].GET_Checker()->GET_X();
			wy = cell[i].GET_Checker()->GET_Y();
			wz = 0.00;
		}
		else { continue; }
		glGetIntegerv(GL_VIEWPORT, viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
		glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
		double dx, dy, dz;
		gluProject(wx, wy, wz, mvMatrix, projMatrix, viewport, &dx, &dy, &dz);
		dy = viewport[3] - dy - 1;
		double d = (x - dx) * (x - dx) + (y - dy) * (y - dy);
		if (d < minDist)
		{
			minDist = d;
			jMin = i;
		}
	}
	if (minDist < 800) {
		if (step == 1 && cell[jMin].GET_Checker()->GET_Color() == 0 || step == -1 && cell[jMin].GET_Checker()->GET_Color() == 1)
		{
			ammount = jMin;
			return 1;
		}
		return 0;
	}
	else { return 0; }
}

bool logic::ToFindCell(board* cell, board* Acell, int x, int y, int& ammount, int step)
{
	int viewport[4];
	int iMin = -1, jMin = -1;
	double mvMatrix[16], projMatrix[16];
	double minDist = 1000;
	for (int i = 0; i < 32; i++) {
		double wx, wy, wz;
		wx = cell[i].GETX();
		wy = cell[i].GETY();
		wz = 0.0;
		glGetIntegerv(GL_VIEWPORT, viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
		glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
		double dx, dy, dz;
		gluProject(wx, wy, wz, mvMatrix, projMatrix, viewport, &dx, &dy, &dz);
		dy = viewport[3] - dy - 1;
		double d = (x - dx) * (x - dx) + (y - dy) * (y - dy);
		if (d < minDist)
		{
			minDist = d;
			jMin = i;
		}
	}
	if (minDist < 800) {
		ammount = jMin;
		if (Acell->GET_Checker()->GET_DAME())
		{
			board* hCLW = Acell, *hCRW = Acell, *hCLB = Acell, *hCRB = Acell;
			while (1) {
				hCLW = hCLW->GETL_White();
				if (hCLW == NULL)
					break;
				if (hCLW->GET_Presence() && hCLW != Acell)
					break;
				if (hCLW == &cell[ammount] && !hCLW->GET_Presence())
					return 1;
			}
			while (1) {
				hCRW = hCRW->GETR_White();
				if (hCRW == NULL)
					break;
				if (hCRW->GET_Presence() && hCRW != Acell)
					break;
				if (hCRW == &cell[ammount] && !hCRW->GET_Presence())
					return 1;
			}
			while (1) {
				hCLB = hCLB->GETL_Black();
				if (hCLB == NULL)
					break;
				if (hCLB->GET_Presence() && hCLB != Acell)
					break;
				if (hCLB == &cell[ammount] && !hCLB->GET_Presence())
					return 1;
			}
			while (1) {
				hCRB = hCRB->GETR_Black();
				if (hCRB == NULL)
					break;
				if (hCRB->GET_Presence() && hCLB != Acell)
					break;
				if (hCRB == &cell[ammount] && !hCRB->GET_Presence())
					return 1;
			}
			return 0;
		}
		else
		{
			if (Acell->GETL_Black() == &cell[ammount] || Acell->GETR_Black() == &cell[ammount] || Acell->GETL_White() == &cell[ammount] || Acell->GETR_White() == &cell[ammount]) {
				if (step == 1) {
					if (Acell->GETL_White() == &cell[ammount] && !cell[ammount].GET_Presence())
						return 1;
					if (Acell->GETR_White() == &cell[ammount] && !cell[ammount].GET_Presence())
						return 1;
				}
				else {
					if (Acell->GETL_Black() == &cell[ammount] && !cell[ammount].GET_Presence())
						return 1;
					if (Acell->GETR_Black() == &cell[ammount] && !cell[ammount].GET_Presence())
						return 1;
				}
			}
		}
	}
	return 0;
}

bool logic::TheFarestCell(board* cell, board* Acell, int x, int y, int& ammount, int step) {
	int c;
	(step == 1) ? c = 1 : c = 0;
	int viewport[4];
	int iMin = -1, jMin = -1;
	double mvMatrix[16], projMatrix[16];
	double minDist = 1000;
	for (int i = 0; i < 32; i++) {
		double wx, wy, wz;
		wx = cell[i].GETX();
		wy = cell[i].GETY();
		wz = 0.0;
		glGetIntegerv(GL_VIEWPORT, viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
		glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
		double dx, dy, dz;
		gluProject(wx, wy, wz, mvMatrix, projMatrix, viewport, &dx, &dy, &dz);
		dy = viewport[3] - dy - 1;
		double d = (x - dx) * (x - dx) + (y - dy) * (y - dy);
		if (d < minDist) {
			minDist = d;
			jMin = i;
		}
	}
	if (minDist < 800) {
		ammount = jMin; int c;
		(Acell->GET_Checker()->GET_Color() == 0) ? c = 1 : c = 0;
		if (Acell->GET_Checker()->GET_DAME()) {
			board* hCLW = Acell, *hCRW = Acell, *hCLB = Acell, *hCRB = Acell;
			int k = 0;
			while (1) {
				hCLW = hCLW->GETL_White();
				if (hCLW == NULL)
					break;
				if (hCLW->GET_Presence() && !hCLW->GET_Checker()->GET_Color() == c)
					break;
				if (hCLW->GET_Presence() && hCLW->GET_Checker()->GET_Color() == c)
					k++;
				if (k > 1)
					break;
				if (hCLW == &cell[ammount] && !hCLW->GET_Presence())
					return 1;
			}
			k = 0;
			while (1) {
				hCRW = hCRW->GETR_White();
				if (hCRW == NULL)
					break;
				if (hCRW->GET_Presence() && !hCRW->GET_Checker()->GET_Color() == c)
					break;
				if (hCRW->GET_Presence() && hCRW->GET_Checker()->GET_Color() == c)
					k++;
				if (k > 1)
					break;
				if (hCRW == &cell[ammount] && !hCRW->GET_Presence())
					return 1;
			}
			k = 0;
			while (1)
			{
				hCLB = hCLB->GETL_Black();
				if (hCLB == NULL)
					break;
				if (hCLB->GET_Presence() && !hCLB->GET_Checker()->GET_Color() == c)
					break;
				if (hCLB->GET_Presence() && hCLB->GET_Checker()->GET_Color() == c)
					k++;
				if (k > 1)
					break;
				if (hCLB == &cell[ammount] && !hCLB->GET_Presence())
					return 1;
			}
			k = 0;
			while (1)
			{
				hCRB = hCRB->GETR_Black();
				if (hCRB == NULL)
					break;
				if (hCRB->GET_Presence() && !hCRB->GET_Checker()->GET_Color() == c)
					break;
				if (hCRB->GET_Presence() && hCRB->GET_Checker()->GET_Color() == c)
					k++;
				if (k > 1)
					break;
				if (hCRB == &cell[ammount] && !hCRB->GET_Presence())
					return 1;
			}
			return 0;
		}
		else {
			if (step == 1) {
				if ((*Acell).GETL_White() != NULL && (*Acell).GETL_White()->GETL_White() != NULL && (&cell[ammount] == (*Acell).GETL_White()->GETL_White()) && Acell->GETL_White()->GET_Presence() && !Acell->GETL_White()->GETL_White()->GET_Presence() && Acell->GETL_White()->GET_Checker()->GET_Color() == c)
					return 1;
				if ((*Acell).GETR_White() != NULL && (*Acell).GETR_White()->GETR_White() != NULL && (&cell[ammount] == (*Acell).GETR_White()->GETR_White()) && Acell->GETR_White()->GET_Presence() && !Acell->GETR_White()->GETR_White()->GET_Presence() && Acell->GETR_White()->GET_Checker()->GET_Color() == c)
					return 1;
				return 0;
			}
			else {
				if ((*Acell).GETL_Black() != NULL && (*Acell).GETL_Black()->GETL_Black() != NULL && (&cell[ammount] == (*Acell).GETL_Black()->GETL_Black()) && Acell->GETL_Black()->GET_Presence() && !Acell->GETL_Black()->GETL_Black()->GET_Presence() && Acell->GETL_Black()->GET_Checker()->GET_Color() == c)
					return 1;
				if ((*Acell).GETR_Black() != NULL && (*Acell).GETR_Black()->GETR_Black() != NULL && (&cell[ammount] == (*Acell).GETR_Black()->GETR_Black()) && Acell->GETR_Black()->GET_Presence() && !Acell->GETR_Black()->GETR_Black()->GET_Presence() && Acell->GETR_Black()->GET_Checker()->GET_Color() == c)
					return 1;
				return 0;
			}
		}
	}
	else { return 0; }
}
