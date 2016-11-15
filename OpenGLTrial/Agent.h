#pragma once
#include <vector>
#include "Cell.h"
#include "Text.h"

using namespace std;

class Agent {
	vector<Cell *> path;
	vector<GLfloat> pathColor;
	double fitness;
	Text health;
	int healthPoints;

	Agent();
	Agent(const vector<Cell *> &cells, const vector<GLfloat> &color, const double fitness);
	void addCell(Cell * newCell);
	void addColor(const vector<GLfloat> &color);
	void setColor();
	void lowerHealth(const int);
};