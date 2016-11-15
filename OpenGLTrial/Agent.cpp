#include "Agent.h"

Agent::Agent() {
	fitness = 0;
}

Agent::Agent(const vector<Cell *> &cells, const vector<GLfloat> &color, const double fitness) {
	path = cells;
	pathColor = color;
	this->fitness = fitness;
}

void Agent::addCell(Cell * newCell) {
	path.push_back(newCell);
}

void Agent::addColor(const vector<GLfloat> &color) {
	for (int i = 0; i < color.size(); i++) {
		pathColor.push_back(color.at(i));
	}
}

void Agent::setColor() {
	for (int i = 0; i < path.size(); i++) {
		path.at(i)->setRedValue(pathColor[0]);
		path.at(i)->setGreenValue(pathColor[1]);
		path.at(i)->setBlueValue(pathColor[2]);
	}
}

void Agent::lowerHealth(const int h) {
	healthPoints -= h;
}
