#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include "Quad.h"
#include "Cell.h"
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <iostream>

using namespace std;

struct Agent {
	vector<Cell *> path;
	vector<GLfloat> pathColor;
	double fitness;

	Agent() { fitness = 0; }
	Agent(const vector<Cell *> &cells, const vector<GLfloat> &color, const double fitness) {
		path = cells;
		pathColor = color;
		this->fitness = fitness;  
	}

	void addCell(Cell * newCell) {
		path.push_back(newCell);
	}

	void addColor(const vector<GLfloat> &color) {
		for (int i = 0; i < color.size(); i++) {
			pathColor.push_back(color.at(i));
		}
	}

	void setColor() {
		for (int i = 0; i < path.size(); i++) {
			path.at(i)->setRedValue(pathColor[0]);
			path.at(i)->setGreenValue(pathColor[1]);
			path.at(i)->setBlueValue(pathColor[2]);
		}
	}
}; 

class Maze
{
private:
	const GLfloat X_OFFSET = 0.07;  //distance from left side of window
	const GLfloat Y_OFFSET = 0.07;  //distance from top side of window
	const GLfloat X_TOPLEFT = -1.0; //x value of top left of window
	const GLfloat Y_TOPLEFT = 1.0;  //y value of top left of window
	int width;					  //number of cells in each row
	int height;					  //number of rows in maze
	int size;					  //number of cells in maze
	vector<Cell> cells;			  //the cells of the maze
	Cell startCell;
	Cell endCell;
	bool GA;					  //indicates if GA is running
	vector<GLfloat> pathColor;
	vector<Agent> agents;         //represent a generation of paths produced by the Genetic Algorithm
public:
	Maze(int width, int height);
	void drawCells();
	void initializeCells();
	void drawLines();
	void createMaze();
	void setStart(int);
	void setEnd(int);
	void setTrap(int);
	void setPath(int);
	int getSize();
	int clickedCell(GLfloat, GLfloat);

	void BFS();
	void DFS();
	double agentRoute(const vector<int> &path, const vector<GLfloat> &pathColor);
	void getAdjacents(Cell cell, vector<Cell *> &adjacentCells);
	void highlightPath();
	void Dijkstra();
	void randomize();
	void drawAgentPath(int index);
};

