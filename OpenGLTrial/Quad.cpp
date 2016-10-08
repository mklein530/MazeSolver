#include "Quad.h"

Quad::Quad(GLfloat r, GLfloat g, GLfloat b, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}

Quad::Quad() {
	this->r = 0.0f;
	this->g = 0.0f;
	this->b = 0.0f;
	this->x1 = 0.0f;
	this->y1 = 0.0f;
	this->x2 = 0.0f;
	this->y2 = 0.0f;
}

void Quad::setWidth(GLfloat width) {
	this->width = width;
}

void Quad::setHeight(GLfloat height) {
	this->height = height;
}

void Quad::setRedValue(GLfloat r) {
	this->r = r;
}

void Quad::setGreenValue(GLfloat g) {
	this->g = g;
}

void Quad::setBlueValue(GLfloat b) {
	this->b = b;
}

void Quad::setX1(GLfloat x1) {
	this->x1 = x1;
}

void Quad::setY1(GLfloat y1) {
	this->y1 = y1;
}

void Quad::setX2(GLfloat x2) {
	this->x2 = x2;
}

void Quad::setY2(GLfloat y2) {
	this->y2 = y2;
}

GLfloat Quad::getWidth() { return x2 - x1; }
GLfloat Quad::getHeight() { return y1 - y2; }
GLfloat Quad::getRedValue() { return r; }
GLfloat Quad::getGreenValue() { return g; }
GLfloat Quad::getBlueValue() { return b; }
GLfloat Quad::getX1() { return x1; }
GLfloat Quad::getY1() { return y1; }
GLfloat Quad::getX2() { return x2; }
GLfloat Quad::getY2() { return y2; }

void Quad::draw() {
	glBegin(GL_TRIANGLES);
	glColor3f(r, g, b);
	//triangle one
	glVertex2f(x1, y1);   //top left
	glVertex2f(x1, y2);   //bottom left
	glVertex2f(x2, y1);   //top right
	//triangle two
	glVertex2f(x2, y2);	  //bottom right
	glVertex2f(x1, y2);   //bottom left
	glVertex2f(x2, y1);   //top right
	glEnd();
}

void Quad::setColor(GLfloat r, GLfloat g, GLfloat b) {
	this->setRedValue(r);
	this->setBlueValue(b);
	this->setGreenValue(g);
}
