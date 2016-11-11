#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(double crossoverRate, double mutationRate, int popSize, int chromLength, int geneLength) {
	this->crossoverRate = crossoverRate;
	this->mutationRate = mutationRate;
	this->popSize = popSize;
	this->chromLength = chromLength;
	this->geneLength = geneLength;
	generation = 0;
	totalFitnessScore = 0;
}

void GeneticAlgorithm::mutate(vector<geneType> &chromosome) {
	for (int i = 0; i < chromosome.size(); i++) {
		//determine if bit shoudl be flipped
		if (randFloat() < mutationRate) {
			chromosome.at(i) = !chromosome.at(i);
		}
	}
}
void GeneticAlgorithm::crossover(const vector<geneType> &mom,
	const vector<geneType> &dad,
	vector<geneType> &child1,
	vector<geneType> &child2) {
	if (randFloat() > crossoverRate || mom == dad) {
		child1 = mom;
		child2 = dad;

		return;
	}

	int crossoverPoint = randInt(0, chromLength - 1);

	for (int i = 0; i < crossoverPoint; i++) {
		child1.push_back(mom.at(i));
		child2.push_back(mom.at(i));
	}

	for (int i = crossoverPoint; i < mom.size(); i++) {
		child1.push_back(dad.at(i));
		child2.push_back(mom.at(i));
	}
}

//roulette wheel selection
Genome& GeneticAlgorithm::selection() {
	double randomFitness = randFloat() * totalFitnessScore;

	double currentFitnessTotal = 0;
	int selectedGenome = 0;

	for (int i = 0; i < popSize; i++) {
		currentFitnessTotal += population.at(i).fitness;

		if (currentFitnessTotal > randomFitness) {
			selectedGenome = i;
			break;
		}
	}

	return population.at(selectedGenome);
}

//update the genome fitness with the new fitness scores and 
//calculates the highest fitness and the fittest member of the population
void GeneticAlgorithm::updateFitnessScores() {
	fittestGenome = 0;
	bestFitnessScore = 0;
	totalFitnessScore = 0;

	//mazeCopy = currentMaze

	for (int i = 0; i < popSize; i++) {
		//decode chromosome
		vector<int> directions = decode(population.at(i).chromosome);

		//get fitness score
		//population.at(i).fitness = testRoute(directions, mazeCopy)

		//update total
		totalFitnessScore += population.at(i).fitness;

		//if fittest genome so far
		if (population.at(i).fitness > bestFitnessScore) {
			bestFitnessScore = population.at(i).fitness;

			fittestGenome = i;

			if (population.at(i).fitness == 1) {
				//found solution
				//display solution
			}
		}
	}
	
}

vector<int> GeneticAlgorithm::decode(const vector<int> &bits) {
	vector<int> directions;

	for (int gene = 0; gene < bits.size(); gene += geneLength) {
		vector<int> currentGene;

		for (int bit = 0; bit < geneLength; bit++) {
			currentGene.push_back(bits.at(gene + bit));
		}

		directions.push_back(binToInt(currentGene));
	}

	return directions;
}

//vector<int> GeneticAlgorithm::decode(const vector<double> &bits) {
//
//}

int GeneticAlgorithm::binToInt(const vector<int> &v) {
	int value = 0;
	int multiplier = 1;

	for (int bit = v.size(); bit > 0; bit--) {
		value += v.at(bit - 1) * multiplier;

		multiplier *= 2;
	}

	return value;
}

void GeneticAlgorithm::createStartPopulation() {
	population.clear();

	for (int i = 0; i < popSize; i++) {
		population.push_back(Genome(chromLength));
	}

	//set all stats to 0
	generation = 0;
	fittestGenome = 0;
	bestFitnessScore = 0;
	totalFitnessScore = 0;
}


void GeneticAlgorithm::epoch() {
	updateFitnessScores();

	//create a new population
	int genomeAmt = 0;

	//vector of new genomes
	vector<Genome> newGenomes;

	while (genomeAmt < popSize) {
		//get 2 parents
		Genome mom = selection();
		Genome dad = selection();

		//crossover
		Genome baby1, baby2;
		crossover(mom.chromosome, dad.chromosome, baby1.chromosome, baby2.chromosome);

		//mutate
		mutate(baby1.chromosome);
		mutate(baby2.chromosome);

		//add to new population
		newGenomes.push_back(baby1);
		newGenomes.push_back(baby2);

		genomeAmt += 2;
	}

	//copy children into original population
	population = newGenomes;

	//new generation created
	++generation;
}

int GeneticAlgorithm::currentGeneration() {
	return generation;
}

int GeneticAlgorithm::getFittestGenome() {
	return fittestGenome;
}
