#include "Cell.h"
#include <iostream>

using namespace std;
#define CELLS_IN_ROW 20

Cell::Cell() {
	this->rowNum = 0;
	this->colNum = 0;
	this->start = false;
	this->end = false;
	this->trap = false;
	this->visited = false;
	this->wall = true;
	color = "empty";
	this->parent = 0;
	this->marked = false;
	this->shortestPath = false;
	this->idNumber = 0;
	this->agent = false;
}

Cell::Cell(int rowNum, int colNum) : Quad() {
	this->rowNum = rowNum;
	this->colNum = colNum;
	this->start = false;
	this->end = false;
	this->trap = false;
	this->visited = false;
	this->wall = true;
	color = "empty";
	this->parent = 0;
	this->marked = false;
	this->shortestPath = false;
	this->idNumber = (rowNum - 1) * CELLS_IN_ROW + colNum;
	this->agent = false;

}

Cell::Cell(int rowNum, int colNum, double r, double g, double b, double x1, double y1, double x2, double y2) :
	Quad(r, g, b, x1, y1, x2, y2)
{
	this->rowNum = rowNum;
	this->colNum = colNum;
	this->start = false;
	this->end = false;
	this->trap = false;
	this->visited = false;
	this->wall = true;
	this->marked = false;
	color = "empty";
	this->parent = 0;
	this->shortestPath = false;
	this->idNumber = (rowNum - 1)*CELLS_IN_ROW + colNum;
	this->agent = false;

}

void Cell::setShortestPath() { shortestPath = true;  }

bool Cell::isMarked() { return marked; }

void Cell::setMarked(bool marked) {
	this->marked = marked;
}

bool Cell::isAgent() { return agent; }

void Cell::setAgent(bool a) { agent = a; }

int Cell::getRowNum() { return rowNum; }

void Cell::setParent(int number) {
	this->parent = number;
}

int Cell::getParent() { return parent; }

int Cell::getColNum() { return colNum; }

bool Cell::hasBeenVisited() { return visited; }

bool Cell::isWall() { return wall; }

bool Cell::isStart() { return start; }

bool Cell::isEnd() { return end; }

bool Cell::isTrap() { return trap; }

void Cell::setVisited(bool v) {
	visited = v;
}

void Cell::setStart() { 
	start = true;
	setPath();
}

void Cell::setEnd() {
	end = true;
	setPath();
}

void Cell::setTrap() {
	trap = true;
}

void Cell::setPath() {
	wall = false;
}

bool Cell::isPath() {
	return wall == false;
}

void Cell::printColor() {
	cout << color << endl;
}

void Cell::setID(int ID) {
	idNumber = ID;
}

int Cell::getIDNumber() { return idNumber; }

void Cell::setCellColor() {
	if (shortestPath && !start && !end) {
		setColor(0.2f, 0.6f, 0.5f);
	}
	else if (agent && !start && !end)
		setColor(getRedValue(), getGreenValue(), getBlueValue());
	else if (visited && !start && !end)
		setColor(1.0f, 0.5f, 0.0f);
	else if (wall)
		setColor(0.5f, 0.5f, 0.5f);
	else if (start)
		setColor(0.0f, 0.0f, 1.0f);
	else if (end)
		setColor(0.0f, 1.0f, 0.0f);
	else if (trap)
		setColor(1.0f, 0.0f, 0.0f);
	else setColor(1.0f, 1.0f, 1.0f);
}

void Cell::setCellColor(GLfloat r, GLfloat g, GLfloat b) {
	if (!start && !end) {
		setColor(r, g, b);
	}
}

void Cell::reset() {
	shortestPath = false;
	visited = false;
	wall = true;
	start = false;
	end = false;
	trap = false;
	agent = false;
}
