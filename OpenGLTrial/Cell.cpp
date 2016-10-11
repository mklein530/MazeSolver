#include "Cell.h"
#include <iostream>

using namespace std;

Cell::Cell() {
	this->rowNum = 0;
	this->colNum = 0;
	start = false;
	end = false;
	trap = false;
	visited = false;
	wall = true;
	color = "empty";
	this->parent = 0;
	marked = false;
	shortestPath = false;
	idNumber = 0;
}

Cell::Cell(int rowNum, int colNum) : Quad() {
	this->rowNum = rowNum;
	this->colNum = colNum;
	start = false;
	end = false;
	trap = false;
	visited = false;
	wall = true;
	color = "empty";
	this->parent = 0;
	marked = false;
	shortestPath = false;
	idNumber = (rowNum - 1) * 12 + colNum;
}

Cell::Cell(int rowNum, int colNum, double r, double g, double b, double x1, double y1, double x2, double y2) :
	Quad(r, g, b, x1, y1, x2, y2)
{
	this->rowNum = rowNum;
	this->colNum = colNum;
	start = false;
	end = false;
	trap = false;
	visited = false;
	wall = true;
	marked = false;
	color = "empty";
	this->parent = 0;
	shortestPath = false;
	idNumber = (rowNum - 1)*12 + colNum;
}

void Cell::setShortestPath() { shortestPath = true;  }

bool Cell::isMarked() { return marked; }

void Cell::setMarked(bool marked) {
	this->marked = marked;
}

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

void Cell::setVisited() {
	visited = true;
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
	if (shortestPath) {
		setColor(0.2f, 0.6f, 0.5f);
	}
	else if (visited) {
		setColor(1.0f, 0.5f, 0.0f);
		color = "orange";
	}
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