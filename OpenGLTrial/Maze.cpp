#include "Maze.h"
#include <functional>
#include <memory>

Maze::Maze(int width, int height){
	this->width = width;
	this->height = height;
	this->size = width*height;
	
	createMaze();
}

int Maze::getSize() {
	return this->size;
}

void Maze::createMaze() {
	for (int i = 1; i <= height; i++) {
		for (int j = 1; j <= width; j++) {
			Cell cell(i, j);
			cells.push_back(cell);
		}
	}
}

//draws from top left of window, where x = -1, y = 1
void Maze::drawCells() {
	int row = 1;
	//start at top left of window, adjust for offset
	for (GLfloat y = (Y_TOPLEFT - Y_OFFSET); row <= height; y -= Y_OFFSET) {
		int col = 1;
		for (GLfloat x = (X_TOPLEFT + X_OFFSET); col <= width; x += X_OFFSET) {
			int currentCell = ( (row - 1)*width + col - 1 );
			cells.at(currentCell).setX1(x);
			cells.at(currentCell).setX2(x + X_OFFSET);
			cells.at(currentCell).setY1(y);
			cells.at(currentCell).setY2(y - Y_OFFSET);
			cells.at(currentCell).setCellColor();
			cells.at(currentCell).draw();
			col++;
		}
		row++;
	}
}

//need to figure out a better way to do this
void Maze::drawLines() {
	GLfloat startX = X_TOPLEFT + X_OFFSET;
	GLfloat startY = Y_TOPLEFT - Y_OFFSET;
	GLfloat endY = (GLfloat)Y_TOPLEFT - (height*Y_OFFSET) - Y_OFFSET;
	GLfloat endX = (GLfloat)X_TOPLEFT + (width*X_OFFSET) + X_OFFSET;

	/*************Draw Vertical Lines*************/
	int col = 0;
	while (col <= width) {
		glBegin(GL_LINES);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f(startX, startY);
		glVertex2f(startX, endY);
		glEnd();
		startX += X_OFFSET;
		col++;
	}

	startX = X_TOPLEFT + X_OFFSET;
	int row = 0;
	/*************Draw Horizontal Lines***********/
	while (row <= height) {
		glBegin(GL_LINES);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f(startX, startY);
		glVertex2f(endX, startY);
		glEnd();
		startY -= Y_OFFSET;
		row++;
	}
}

int Maze::clickedCell(GLfloat mx, GLfloat my) {
	//linear comparison of all x and y coordinates of squares
	for (int i = 0; i < cells.size(); i++) {
		Cell currentCell = cells.at(i);
		if (mx > currentCell.getX1() && mx < currentCell.getX2() &&
			my < currentCell.getY1() && my > currentCell.getY2()) {
			//this is the clicked square
			return i;
		}
	}
	return -1;
}

// tried using the Cell objects themselves as parameters and didn't work
// need to pratice altering object properties using references and pointersB
void Maze::setStart(int index) {
	cells.at(index).setStart();
	startCell = cells.at(index);
}

void Maze::setEnd(int index){
	cells.at(index).setEnd();
	endCell = cells.at(index);
}

void Maze::setTrap(int index) {
	cells.at(index).setTrap();
}

void Maze::setPath(int index) {
	cells.at(index).setPath();
}

void Maze::BFS() {
	queue<Cell *> visited;
	vector<Cell *> neighbors;
	vector<Cell> inPath;
	vector<Cell> *mazePtr = &cells;
	//printf("x1: %f\nx2: %f\n", startCell.getX1(), startCell.getX2());
	visited.push(&startCell);
	int i = 1;
	while (!visited.empty()) {
		i++; //debug purposes
		Cell * currentCell = visited.front();
		currentCell->setVisited();
		getAdjacents(*currentCell, neighbors);
		visited.pop();
		if (currentCell->isEnd()) {
			printf("iteration %d\n", i);
			currentCell->setVisited();
			//currentCell.setCellColor();
			break;
		}
		else {
			//for each neighbor of currentCell
			 for (int i = 0; i < neighbors.size(); i++) {
				//debug purposes
				printf("neighbor amount: %d\n", neighbors.size());
				//if neighbor is unvisited
				if (!neighbors.at(i)->hasBeenVisited()) {
					//mark neighbor as visited
					neighbors.at(i)->setVisited();
					neighbors.at(i)->setCellColor();
					//for debugging
					printf("x1: %f\nx2: %f\n", neighbors.at(i)->getX1(), neighbors.at(i)->getX2());
					//enqueue neighbor
					visited.push(neighbors.at(i));
				}
			 }	
			//mark currentCell examined
		}
	}
	/*for (vector<Cell>::iterator i = cells.begin(); i != cells.end(); i++) {
		if (i->hasBeenVisited()) {
			i->setCellColor();
			i->printColor();
		}
	}*/
	//glutPostRedisplay();
}

void Maze::getAdjacents(Cell cell, vector<Cell *> & adjacentCells) {
	const int MAX_ADJACENTS = 4;
	int row = cell.getRowNum();
	int col = cell.getColNum();
	int indices[MAX_ADJACENTS][2] = { {row - 1, col},
									  {row, col + 1},
									  {row, col - 1},
									  {row + 1, col}
	};

	for (int i = 0; i < MAX_ADJACENTS; i++) {
		for (int j = 0; j < cells.size(); j++) {
			//if row and col numbers are the same, cell is adjacent
			if ( !cells.at(j).isWall() && indices[i][0] == cells.at(j).getRowNum() &&
				indices[i][1] == cells.at(j).getColNum() )
				adjacentCells.push_back(&cells.at(j));
		}
	}
}