#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include "Quad.h"
#include "Cell.h"
#include <vector>
#include <queue>
#include <list>

using namespace std;

class Maze
{
private:
	const GLfloat X_OFFSET = 0.1;  //distance from left side of window
	const GLfloat Y_OFFSET = 0.1;  //distance from top side of window
	const GLfloat X_TOPLEFT = -1.0; //x value of top left of window
	const GLfloat Y_TOPLEFT = 1.0;  //y value of top left of window
	int width;					  //number of cells in each row
	int height;					  //number of rows in maze
	int size;					  //number of cells in maze
	vector<Cell> cells;			  //the cells of the maze
	Cell startCell;
	Cell endCell;
public:
	Maze(int width, int height);
	void drawCells();
	void drawLines();
	void createMaze();
	void setStart(int);
	void setEnd(int);
	void setTrap(int);
	void setPath(int);
	int getSize();
	int clickedCell(GLfloat, GLfloat);

	void BFS();
	void getAdjacents(Cell cell, vector<Cell *> & adjacentCells);
};

