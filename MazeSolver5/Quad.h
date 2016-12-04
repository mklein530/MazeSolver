#pragma once

#include <GL\glew.h>
#include <GL\freeglut.h>

class Quad {
private:
	GLfloat width;
	GLfloat height;
	GLfloat r, g, b;
	GLfloat x1, y1; //top left coordinates
	GLfloat x2, y2; //bottom right coordinates
public:

	Quad(GLfloat r, GLfloat g, GLfloat b, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
	Quad();

	void setWidth(GLfloat);
	void setHeight(GLfloat);
	void setRedValue(GLfloat);
	void setGreenValue(GLfloat);
	void setBlueValue(GLfloat);
	void setX1(GLfloat);
	void setY1(GLfloat);
	void setX2(GLfloat);
	void setY2(GLfloat);

	GLfloat getWidth();
	GLfloat getHeight();
	GLfloat getRedValue();
	GLfloat getGreenValue();
	GLfloat getBlueValue();
	GLfloat getX1();
	GLfloat getY1();
	GLfloat getX2();
	GLfloat getY2();

	void draw();
	void setColor(GLfloat, GLfloat, GLfloat);
};
