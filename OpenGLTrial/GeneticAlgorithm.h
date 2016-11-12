#pragma once
#include <vector>
#include "Maze.h"
#include "utility.h"

using namespace std;
using geneType = int;

struct Genome {
	vector<geneType> chromosome;
	double fitness;
	Genome() : fitness(0) {}
	Genome(const int numBits) {
		//create a random bit string
		for (int i = 0; i < numBits; i++) {
			chromosome.push_back(randInt(0, 1));
		}
	}
};

class GeneticAlgorithm {
private:
	vector<Genome> population;
	int popSize;
	double crossoverRate;
	double mutationRate;
	int chromLength; //bits per chromosome
	int geneLength; //bits per gene
	int fittestGenome;
	double bestFitnessScore;
	double totalFitnessScore;
	int generation;  //current generation number
	Maze * maze;

	void mutate(vector<geneType> &chromosome);
	void crossover(const vector<geneType> &mom,
				   const vector<geneType> &dad,
				   vector<geneType> &child1,
				   vector<geneType> &child2);
	Genome& selection(); //roulette wheel selection

	//update the genome fitness with the new fitness scores and 
	//calculates the highest fitness and the fittest member of the population
	void updateFitnessScores();

	vector<int> decode(const vector<int> &bits);
	vector<int> decode(const vector<double> &bits);

	int binToInt(const vector<int> &v);

	void createStartPopulation();

public:
	GeneticAlgorithm(double crossoverRate, double mutationRate, int popSize, int chromLength, int geneLength, Maze *);

	void epoch();

	int currentGeneration();

	int getFittestGenome();
};

