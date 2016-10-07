#include "Maze.h"


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
	for (GLfloat y = (Y_TOPLEFT - Y_OFFSET); row < height; y -= Y_OFFSET) {
		int col = 1;
		for (GLfloat x = (X_TOPLEFT + X_OFFSET); col < width; x += X_OFFSET) {
			int currentCell = (row - 1)*width + col;
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

void Maze::drawLines() {
	GLfloat startX = X_TOPLEFT + X_OFFSET;
	GLfloat startY = Y_TOPLEFT - Y_OFFSET;
	GLfloat endY = (GLfloat)Y_TOPLEFT - (height*Y_OFFSET);
	GLfloat endX = (GLfloat)X_TOPLEFT + (width*X_OFFSET);

	/*************Draw Vertical Lines*************/
	int col = 1;
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
	int row = 1;
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

void Maze::setStart(int index) {
	cells.at(index).setStart();
}

void Maze::setEnd(int index){
	cells.at(index).setEnd();
}

void Maze::setTrap(int index) {
	cells.at(index).setTrap();
}

void Maze::setPath(int index) {
	cells.at(index).setPath();
}