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
	string color;
public:
	Cell();
	Cell(int rowNum, int colNum);
	Cell(int rowNum, int colNum, double r, double g, double b, double x1, double y1, double x2, double y2);

	bool isWall();
	bool isStart();
	bool isEnd();
	bool isTrap();
	bool hasBeenVisited();
	int getRowNum();
	int getColNum();

	void setVisited();
	void setStart();
	void setEnd();
	void setTrap();
	void setPath();
	void setCellColor();
	void printColor();
};

