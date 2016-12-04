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

Maze maze(20,20);
GeneticAlgorithm GA(CROSSOVER_RATE, MUTATION_RATE, POP_SIZE, CHROM_LENGTH, GENE_LENGTH, &maze);
int index = 0;
int epochs = 0;
void onKeyPress(unsigned char key, int x, int y) {
	switch (key) {
		case 13: {
			maze.randomize();
		}
			break;
		case 103: {
			//index tells the maze which agent to draw
			if (index % POP_SIZE == 0) {
				index = 0;
			}
			maze.drawAgentPath(index++);
		}
			break;
		case 98: {
			maze.BFS();
		}
			break;
		case 100: {
			maze.DFS();
		}
			break;
		case 110: {
			//index tells the maze which agent to draw
			if (index % POP_SIZE == 0) {
				index = 0;
				GA.epoch();
			}
			maze.drawAgentPath(index++);
		}
			break;
		case 101: {
			GA.epoch();
		}
			break;
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
	//GA.calculateNotableScores();

	/***hackish way to display genetic algorithm stats
		needs to be generalized and cleaned up; pressed for time***/
	GLfloat textX = 0.5f;
	GLfloat textY = 0.7f;
	//best fitness
	char * bestFit = (char *)malloc(sizeof(char) * 3);
	sprintf(bestFit, "%.3f", GA.bestFitness());
	char * textArray = "Best Fitness: ";
	Text text(textArray, GLUT_BITMAP_HELVETICA_18, textX, textY, { 0.0f, 0.0f, 0.0f });
	Text bestFitness(bestFit, GLUT_BITMAP_HELVETICA_18, 0.8, textY,{ 0.0f, 0.0f, 0.0f });
	bestFitness.display();
	text.display();

	//worst fitness
	char * worstFit = (char *)malloc(sizeof(char) * 9999);
	sprintf(worstFit, "%.3f", GA.worstFitness());
	char * worstArray = "Worst Fitness: ";
	Text text2(worstArray, GLUT_BITMAP_HELVETICA_18, textX, textY - 0.08, { 0.0f, 0.0f, 0.0f });
	Text worstFitness(worstFit, GLUT_BITMAP_HELVETICA_18, 0.8, textY - 0.08, { 0.0f, 0.0f, 0.0f });
	text2.display();
	worstFitness.display();

	//average fitness
	char * averageFit = (char *)malloc(sizeof(char) * 9999);
	sprintf(averageFit, "%.3f", GA.averageFitness());
	char * averageArray = "Average Fitness: ";
	Text text3(averageArray, GLUT_BITMAP_HELVETICA_18, textX, textY - 0.16, { 0.0f, 0.0f, 0.0f });
	Text averageFitness(averageFit, GLUT_BITMAP_HELVETICA_18, 0.85, textY - 0.16, { 0.0f, 0.0f, 0.0f });
	text3.display();
	averageFitness.display();

	//population size
	char * popSize = (char *)malloc(sizeof(char) * 9999);
	sprintf(popSize, "%d", POP_SIZE);
	char * popString = "Population Size: ";
	Text text4(popString, GLUT_BITMAP_HELVETICA_18, textX, textY - 0.24, { 0.0f, 0.0f, 0.0f });
	Text popDisplay(popSize, GLUT_BITMAP_HELVETICA_18, 0.85, textY - 0.24, { 0.0f, 0.0f, 0.0f });
	text4.display();
	popDisplay.display();

	//chromosome size
	char * chromSize = (char *)malloc(sizeof(char) * 9999);
	sprintf(chromSize, "%d", CHROM_LENGTH);
	char * chromString = "Chromosome Size: ";
	Text text5(chromString, GLUT_BITMAP_HELVETICA_18, textX, textY - 0.32, { 0.0f, 0.0f, 0.0f });
	Text chromDisplay(popSize, GLUT_BITMAP_HELVETICA_18, 0.9, textY - 0.32, { 0.0f, 0.0f, 0.0f });
	text5.display();
	chromDisplay.display();

	//crossover rate 
	char * crossover = (char *)malloc(sizeof(char) * 9999);
	sprintf(crossover, "%.2f", CROSSOVER_RATE);
	char * crossoverString = "Crossover Rate: ";
	Text text6(crossoverString, GLUT_BITMAP_HELVETICA_18, textX, textY - 0.40, { 0.0f, 0.0f, 0.0f });
	Text crossoverDisplay(crossover, GLUT_BITMAP_HELVETICA_18, 0.85, textY - 0.40, { 0.0f, 0.0f, 0.0f });
	text6.display();
	crossoverDisplay.display();

	//mutation rate 
	char * mutation = (char *)malloc(sizeof(char) * 9999);
	sprintf(mutation, "%.3f", MUTATION_RATE);
	char * mutationString = "Mutation Rate: ";
	Text text7(mutationString, GLUT_BITMAP_HELVETICA_18, textX, textY - 0.48, { 0.0f, 0.0f, 0.0f });
	Text mutationDisplay(mutation, GLUT_BITMAP_HELVETICA_18, 0.85, textY - 0.48, { 0.0f, 0.0f, 0.0f });
	text7.display();
	mutationDisplay.display();
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

