#pragma once

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <vector>	

using namespace std;

class Text
{
private:
	const char * GLstring;
	void * font;
	GLfloat x, y;
	vector<GLfloat> color;
public:
	Text();
	Text(const char * text, void * textFont, GLfloat xPos, GLfloat yPos, vector<GLfloat> textColor);
	void display();
};