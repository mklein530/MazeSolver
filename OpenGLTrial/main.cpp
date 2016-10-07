#define _CRT_SECURE_NO_WARNINGS

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include "Maze.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAX_HEALTH 100

using namespace std;

int leftClickCount = 0;
int health = 100;
Maze maze(13, 13);

void onKeyPress(char key, int x, int y) {
	if (key == 13) {
		//train AI to solve maze
	}
}

void onMouseClick(int button, int state, int x, int y) {
	//convert window coordinates to opengl coordinates
	float mx = -1 + 2 * (float)x / SCREEN_WIDTH;
	float my = -1 + 2 * (float)(SCREEN_HEIGHT - y) / SCREEN_HEIGHT;

	int clickedCell = maze.clickedCell(mx, my);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && clickedCell != -1) {
		leftClickCount++;

		if (leftClickCount == 1) {
			//start tile
			maze.setStart(clickedCell);
		}
		else if (leftClickCount == 2) {
			//end tile
			maze.setEnd(clickedCell);
		}
		else if (leftClickCount > 2) {
			//path tile
			maze.setPath(clickedCell);
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && clickedCell != -1) {
		maze.setTrap(clickedCell);
	}
}

void displayMe(void) {
	glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	maze.drawCells();
	maze.drawLines();

	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos2f(0.5, 0.7);

	/*******************Display Health*****************/
	char * healthDisplay = "Health: ";
	int health = 100;
	
	void * font = GLUT_BITMAP_HELVETICA_18;
	for (char *p = healthDisplay; *p != '\0'; p++) {
		glutBitmapCharacter(font, *p);
	}
	
	char* healthString = (char *) malloc(sizeof(char) * 3);
	sprintf(healthString, "%d", health);
	for (int i = 0; i < 3; i++) {
		glutBitmapCharacter(font, healthString[i]);
	}
	
	
	//  getchar();
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(800, 600);                    // window size
	glutInitWindowPosition(0, 0);                    // distance from the top-left screen
	glutCreateWindow("MazeSolver");                  // message displayed on top bar window
	glutDisplayFunc(displayMe);
	glutIdleFunc(displayMe);
	glutMouseFunc(onMouseClick);
	glutMainLoop();
	return 0;
}

