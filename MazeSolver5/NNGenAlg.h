//#pragma once
//#include <vector>
//#include "Maze.h"
//#include "utility.h"
//#include "Text.h"
//
//using namespace std;
//using geneType = double;
//
//struct Genome {
//	vector<geneType> chromosome;
//	double fitness;
//	int health;
//	vector<GLfloat> chromColor; //color of the path
//	Genome() : fitness(0) {}
//	Genome(const int numBits, const GLfloat r, const GLfloat g, const GLfloat b) {
//		//create a random bit string
//		for (int i = 0; i < numBits; i++) {
//			chromosome.push_back(randInt(0, 1));
//		}
//		chromColor = { r, g, b };
//		health = 100;
//	}
//
//	friend bool operator<(const Genome& lhs, const Genome& rhs) {
//		return (lhs.fitness < rhs.fitness);
//	}
//};
//
//class NNGenAlg {
//private:
//	vector<Genome> population;
//	int popSize;
//	double crossoverRate;
//	double mutationRate;
//	vector<int> splitPoints;
//	int chromLength; //bits per chromosome
//	int geneLength; //bits per gene
//	int fittestGenome;
//	double bestFitnessScore;
//	double totalFitnessScore;
//	double worstFitnessScore;
//	double averageFitnessScore;
//	int generation;  //current generation number
//	Maze * maze;
//
//	void calculateNotableScores();
//	void mutate(vector<geneType> &chromosome);
//	void crossover(const vector<geneType> &mom,
//		const vector<geneType> &dad,
//		vector<geneType> &child1,
//		vector<geneType> &child2);
//	Genome& selection(); //roulette wheel selection
//
//	//update the genome fitness with the new fitness scores and 
//	//calculates the highest fitness and the fittest member of the population
//	void updateFitnessScores();
//
//	vector<int> decode(const vector<int> &bits);
//	vector<int> decode(const vector<double> &bits);
//
//	int binToInt(const vector<int> &v);
//
//	void createStartPopulation();
//
//public:
//	int health;
//	double maxPerturbation;
//	NNGenAlg(double crossoverRate, double mutationRate, int popSize, int chromLength, int geneLength, Maze *);
//
//	void displayHealth(const Genome &genome);
//	void epoch();
//
//	int currentGeneration();
//	double bestFitness() {
//		return bestFitnessScore;
//	}
//	double averageFitness() {
//		return averageFitnessScore;
//	}
//	double worstFitness() {
//		return worstFitnessScore;
//	}
//	double totalFitness() {
//		return totalFitnessScore;
//	}
//	int getFittestGenome();
//};
