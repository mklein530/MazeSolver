#include "Text.h"

Text::Text() {
	GLstring = "";
	font = NULL;
	x = y = 0.0f;
	color = { 0.0f, 0.0f, 0.0f };
}

Text::Text(const char * text, void * textFont, GLfloat xPos, GLfloat yPos, vector<GLfloat> textColor) {
	GLstring = text;
	font = textFont;
	x = xPos;
	y = yPos;
	color = textColor;
}

void Text::display() {
	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos2f(x, y);
	for (const char *p = GLstring; *p != '\0'; p++) {
		glutBitmapCharacter(font, *p);
	}
}

void Text::addText(string newText) {

}

