#include "Maze.h"
#include <functional>
#include <memory>
#include <climits>
#include <random>
#include <time.h>
Maze::Maze(int width, int height){
	this->width = width;
	this->height = height;
	this->size = width*height;
	createMaze();
	initializeCells();
	srand(time(NULL));
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

void Maze::initializeCells() {
	int row = 1;
	//start at top left of window, adjust for offset
	for (GLfloat y = (Y_TOPLEFT - Y_OFFSET); row <= height; y -= Y_OFFSET) {
		int col = 1;
		for (GLfloat x = (X_TOPLEFT + X_OFFSET); col <= width; x += X_OFFSET) {
			int currentCell = ((row - 1)*width + col - 1);
			cells.at(currentCell).setX1(x);
			cells.at(currentCell).setX2(x + X_OFFSET);
			cells.at(currentCell).setY1(y);
			cells.at(currentCell).setY2(y - Y_OFFSET);
			cells.at(currentCell).setID((row - 1)*width + col);
			cells.at(currentCell).setCellColor();
			col++;
		}
		row++;
	}
}
//draws from top left of window, where x = -1, y = 1
void Maze::drawCells() {
	for (vector<Cell>::iterator i = cells.begin(); i != cells.end(); i++) {
		i->setCellColor();
		i->draw(); 
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
// need to pratice altering object properties using references and pointers
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
	visited.push(&startCell);

	while (!visited.empty()) {
		Cell * currentCell = visited.front();
		currentCell->setVisited(true);
		getAdjacents(*currentCell, neighbors);
		visited.pop();
		if (currentCell->isEnd()) {
			currentCell->setVisited(true);
			//set parent to ending cell...not a good way to do it but it works
			//and trying to find the reason other methods weren't working
			//was halting progress too much. will revisit to fix
			for (vector<Cell>::iterator i = cells.begin(); i != cells.end(); i++) {
				if (i->isEnd()) {
					endCell.setParent(currentCell->getParent());
				}
			}
			break;
		}
		else {
			//for each neighbor of currentCell
			 for (int i = 0; i < neighbors.size(); i++) {
				//if neighbor is unvisited
				if (!neighbors.at(i)->hasBeenVisited()) {
					//mark neighbor as visited
					neighbors.at(i)->setVisited(true);
					//set parent to id number of current cell
					neighbors.at(i)->setParent(currentCell->getIDNumber());
					//enqueue neighbor
					visited.push(neighbors.at(i));
				}
			 }	
		}
	}

	highlightPath();
}

void Maze::DFS() {
	//start with an empty stack
	stack<Cell *> S;
	Cell * vertex = &startCell;

	//container for all neighbors of cell being visited
	vector<Cell *> neighbors;

	//set each cell.visited = false
	for (vector<Cell>::iterator i = cells.begin(); i != cells.end(); i++) {
		i->setVisited(false);
	}

	S.push(vertex);

	while (!S.empty()) {
		Cell * currentCell = S.top();
		S.pop();
		if (currentCell->isEnd()) {
			currentCell->setVisited(true);
			for (vector<Cell>::iterator i = cells.begin(); i != cells.end(); i++) {
				if (i->isEnd()) {
					endCell.setParent(currentCell->getParent());
				}
			}
			break;
		}
		else if (!currentCell->hasBeenVisited()) {
			currentCell->setVisited(true);
			getAdjacents(*currentCell, neighbors);
			for (vector<Cell *>::iterator i = neighbors.begin(); i != neighbors.end(); i++) {
				Cell * neighbor = *i;
				if (!neighbor->hasBeenVisited()) {
					neighbor->setParent(currentCell->getIDNumber());
					S.push(neighbor);
				}
			}
		}
	}
	
	highlightPath();
}

void Maze::getAdjacents(Cell cell, vector<Cell *> & adjacentCells) {
	adjacentCells.clear();
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
			if (!cells.at(j).isWall() && indices[i][0] == cells.at(j).getRowNum() &&
				indices[i][1] == cells.at(j).getColNum())
				adjacentCells.push_back(&cells.at(j));
		}
	}
}

void Maze::Dijkstra() {
	//vector<int> distance;
	//vector<int> previous;
	//vector<Cell *> neighbors;
	//distance.at(startCell.getIDNumber() - 1) = 0;
	//priority_queue<int, vector<int>, less<int>> PQ;
	//for (Cell cell : cells) { //for each cell in maze
	//	if (!cell.isWall()) {
	//		int vertex;
	//		if (cell.getIDNumber() != startCell.getIDNumber()) {
	//			vertex = cell.getIDNumber - 1;
	//			distance.at(vertex) = INT_MAX; //unknown distance from start to current cell
	//			previous.at(vertex) = NULL;    //predecessor of vertex is null
	//		}
	//		PQ.push(vertex);
	//	}
	//}

	//while (!PQ.empty()) {
	//	int bestVertex = PQ.top();	//remove and return best vertex
	//	PQ.pop();
	//	getAdjacents(cells.at(bestVertex), neighbors);
	//	//for each neighbor v of bestVertex, where v has not yet been removed from PQ
	//	for (vector<Cell *>::iterator i = neighbors.begin(); i != neighbors.end(); i++) {
	//		int v = (*i)->getIDNumber()-1;
	//		//distance from bestvertex to v
	//		int alt = distance.at(bestVertex) + distanceBetween(bestVertex, v);
	//		//if new distance is smaller than distance to v
	//		if (alt < distance.at(v)) {
	//			distance.at(v) = alt;
	//			previous.at(v) = bestVertex;
	//			//reorder v in PQ, done automatically when push or pop is called
	//		}
	//	}
	//}
}

bool operator <(Cell &lhs, Cell &rhs) {
	return lhs.getIDNumber() < rhs.getIDNumber();
}


// start at the goal node and traverse up the tree to the root
void Maze::highlightPath() {
	Cell thisCell = endCell;
	while (thisCell.getIDNumber() != startCell.getIDNumber()) {
		for (vector<Cell>::iterator i = cells.begin(); i != cells.end(); i++) {
			if (i->getIDNumber() == endCell.getIDNumber())
				i->setShortestPath();
			if (i->getParent() != 0)
				if (i->getIDNumber() == thisCell.getParent()) {
					i->setShortestPath();
					thisCell = *i;
					break;
				}
		}
	}
}

<<<<<<< HEAD
//creates a random map
=======
>>>>>>> 0b8a74961c9e96bf422638600608abc7c0c25c85
void Maze::randomize() {
	//cells.at(randomNumber(cells.size())).setStart();
	//cells.at(randomNumber(cells.size())).setEnd();
	for (vector<Cell>::iterator i = cells.begin(); i != cells.end(); i++) {
		i->reset();
	}
	this->setStart(randomNumber(cells.size()));
	this->setEnd(randomNumber(cells.size()));
	for (vector<Cell>::iterator i = cells.begin(); i != cells.end(); i++) {
		int wall = randomNumber(2); //generate 0 or 1
		if (!wall)
			if(!i->isEnd() && !i->isStart())
				i->setPath();
	}
}

//returns random integer on interval [0, max-1]
int Maze::randomNumber(int max) {
	return rand() % max;
}