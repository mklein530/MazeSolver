#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Quad.h"
#include <string>

using namespace std;

class Cell : public Quad
{
private:
	bool wall;
	bool start, end;
	bool trap;
	bool visited;
	int idNumber;
	int rowNum, colNum;
	bool marked; //all neighbors of cell have been visited (BFS)
	string color;
	int parent; //cell number of parent cell
	bool shortestPath;

public:
	Cell();
	Cell(int rowNum, int colNum);
	Cell(int rowNum, int colNum, double r, double g, double b, double x1, double y1, double x2, double y2);

	int getIDNumber();
	void setID(int ID);
	void setShortestPath();
	bool isMarked();
	void setMarked(bool marked);
	int getParent();
	void setParent(int number);
	bool isWall();
	bool isStart();
	bool isEnd();
	bool isTrap();
	bool isPath();
	bool hasBeenVisited();
	int getRowNum();
	int getColNum();

	void setVisited(bool);
	void setStart();
	void setEnd();
	void setTrap();
	void setPath();
	void setCellColor();
	void printColor();
};

