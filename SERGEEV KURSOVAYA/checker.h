#pragma once

class checker
{
private:
	int color;
	double x, y;
	bool dame;
public:
	checker(double xCenter, double yCenter, int col);
	void Checker();
	double GET_X();
	double GET_Y();
	void SET_X(double x);
	void SET_Y(double y);
	int GET_Color();
	bool GET_DAME();
	void SET_DAME(bool d);
};

