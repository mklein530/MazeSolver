#define _CRT_SECURE_NO_WARNINGS

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <stdio.h>
#include <string>
#include <random>
#include <time.h>
#include <vector>
#include <iostream>
#include "Maze.h"
#include "GeneticAlgorithm.h"
#include "Text.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAX_HEALTH 100

using namespace std;

int health = 100;
Maze maze(20,20);
GeneticAlgorithm GA(CROSSOVER_RATE, MUTATION_RATE, POP_SIZE, CHROM_LENGTH, GENE_LENGTH, &maze);
int index = 0;

void onKeyPress(unsigned char key, int x, int y) {
	switch (key) {
		case 13: {
			maze.randomize();
			GA.epoch();
			index++;
		}
			break;
		case 103: {
			//index tells the maze which agent to draw
			if (index % POP_SIZE == 0) {
				index = 0;
				GA.epoch();
			}
			maze.drawAgentPath(index++);
		}
			break;
		case 98: {
			maze.BFS();
		}
		case 100: {
			maze.DFS();
		}
		default: break;
	}
}

void onMouseClick(int button, int state, int x, int y) {
	//convert window coordinates to opengl coordinates
	float mx = -1 + 2 * (float)x / SCREEN_WIDTH;
	float my = -1 + 2 * (float)(SCREEN_HEIGHT - y) / SCREEN_HEIGHT;
	static int leftClickCount = 0;

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
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && clickedCell != -1) {
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

	Text agentHealth("Health: ", GLUT_BITMAP_HELVETICA_18, 0.5f, 0.7f, { 0.0f, 0.0f, 0.0f });
	agentHealth.display();

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
	glutKeyboardFunc(onKeyPress);
	glutMainLoop();
	return 0;
}

