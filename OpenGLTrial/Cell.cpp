#include "Cell.h"

Cell::Cell(int rowNum, int colNum) : Quad() {
	this->rowNum = rowNum;
	this->colNum = colNum;
}

Cell::Cell(int rowNum, int colNum, double r, double g, double b, double x1, double y1, double x2, double y2) :
	Quad(r, g, b, x1, y1, x2, y2)
{
	this->rowNum = rowNum;
	this->colNum = colNum;
}

int Cell::getRowNum() { return rowNum; }

int Cell::getColNum() { return colNum; }

bool Cell::hasBeenVisited() { return visited; }

bool Cell::isWall() { return wall; }

bool Cell::isStart() { return start; }

bool Cell::isEnd() { return end; }

bool Cell::isTrap() { return trap; }

void Cell::setVisited() {
	this->visited = true;
}

void Cell::setStart() { 
	start = true;
	this->setColor(0.0f, 0.0f, 1.0f);
	this->draw();
}

void Cell::setEnd() {
	end = true;
	this->setColor(0.0f, 1.0f, 0.0f);
	this->draw();
}

void Cell::setTrap() {
	trap = true;
	this->setColor(1.0f, 0.0f, 0.0f);
	this->draw();
}

void Cell::setPath() {
	wall = false;
	this->setColor(0.0f, 0.0f, 0.0f);
	this->draw();
}



