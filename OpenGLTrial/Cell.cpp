#include "Cell.h"

Cell::Cell(int rowNum, int colNum) : Quad() {
	this->rowNum = rowNum;
	this->colNum = colNum;
	start = false;
	end = false;
	trap = false;
	wall = true;
}

Cell::Cell(int rowNum, int colNum, double r, double g, double b, double x1, double y1, double x2, double y2) :
	Quad(r, g, b, x1, y1, x2, y2)
{
	this->rowNum = rowNum;
	this->colNum = colNum;
	start = false;
	end = false;
	trap = false;
	wall = true;
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
}

void Cell::setEnd() {
	end = true;
}

void Cell::setTrap() {
	trap = true;
}

void Cell::setPath() {
	wall = false;
}

void Cell::setCellColor() {
	if (!wall)
		setColor(1.0f, 1.0f, 1.0f);
	else if (start)
		setColor(0.0f, 0.0f, 1.0f);
	else if (end)
		setColor(0.0f, 1.0f, 0.0f);
	else if (trap)
		setColor(1.0f, 0.0f, 0.0f);
	else setColor(0.5f, 0.5f, 0.5f);
}



