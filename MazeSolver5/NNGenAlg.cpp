//#include "NNGenAlg.h"
//
//NNGenAlg::NNGenAlg(double crossoverRate, double mutationRate, int popSize, int chromLength, int geneLength, Maze * maze) {
//	this->crossoverRate = crossoverRate;
//	this->mutationRate = mutationRate;
//	this->popSize = popSize;
//	this->chromLength = chromLength;
//	this->geneLength = geneLength;
//	this->maze = maze;
//
//	maxPerturbation = 0.3;
//	generation = 0;
//	totalFitnessScore = 0;
//	createStartPopulation();
//}
//
//void NNGenAlg::displayHealth(const Genome &genome) {
//	Text agentHealth("Health: " + genome.health, GLUT_BITMAP_HELVETICA_18, 0.5f, 0.7f, { 0.0f, 0.0f, 0.0f });
//	agentHealth.display();
//}
//
//void NNGenAlg::mutate(vector<geneType> &chromosome) {
//	for (int i = 0; i < chromosome.size(); i++) {
//		//determine if bit should be perturbed
//		if (randFloat() < mutationRate) {
//			chromosome.at(i) += (randomClamped()*maxPerturbation);
//		}
//	}
//}
//
////double point crossover
//void NNGenAlg::crossover(const vector<geneType> &mom,
//	const vector<geneType> &dad,
//	vector<geneType> &child1,
//	vector<geneType> &child2) {
//	if (randFloat() > crossoverRate || mom == dad) {
//		child1 = mom;
//		child2 = dad;
//
//		return;
//	}
//
//	int index1 = randInt(0, splitPoints.size() - 2);
//	int index2 = randInt(index1, splitPoints.size() - 1);
//
//	int point1 = splitPoints[index1];
//	int point2 = splitPoints[index2];
//
//	for (int i = 0; i < mom.size(); i++) {
//		if (i < point1 || i >= point2) {
//			child1.push_back(mom[i]);
//			child2.push_back(dad[i]);
//		}
//		else {
//			child1.push_back(dad[i]);
//			child2.push_back(mom[i]);
//		}
//	}
//	return;
//}
//
////roulette wheel selection
//Genome& NNGenAlg::selection() {
//	double randomFitness = randFloat() * totalFitnessScore;
//
//	double currentFitnessTotal = 0;
//	int selectedGenome = 0;
//
//	for (int i = 0; i < popSize; i++) {
//		currentFitnessTotal += population.at(i).fitness;
//
//		if (currentFitnessTotal > randomFitness) {
//			selectedGenome = i;
//			break;
//		}
//	}
//
//	return population.at(selectedGenome);
//}
//
////update the genome fitness with the new fitness scores and 
////calculates the highest fitness and the fittest member of the population
//void NNGenAlg::updateFitnessScores() {
//	fittestGenome = 0;
//	bestFitnessScore = 0;
//	totalFitnessScore = 0;
//
//	//mazeCopy = currentMaze
//
//	for (int i = 0; i < popSize; i++) {
//		//decode chromosome
//		vector<int> directions = decode(population.at(i).chromosome);
//
//		//get fitness score
//		population.at(i).fitness = maze->agentRoute(directions, population.at(i).chromColor);
//
//		//update total
//		totalFitnessScore += population.at(i).fitness;
//
//		//if fittest genome so far
//		if (population.at(i).fitness > bestFitnessScore) {
//			bestFitnessScore = population.at(i).fitness;
//
//			fittestGenome = i;
//
//			if (population.at(i).fitness == 1) {
//				//found solution
//
//			}
//		}
//	}
//}
//
//vector<int> NNGenAlg::decode(const vector<int> &bits) {
//	vector<int> directions;
//
//	for (int gene = 0; gene < bits.size(); gene += geneLength) {
//		vector<int> currentGene;
//
//		for (int bit = 0; bit < geneLength; bit++) {
//			currentGene.push_back(bits.at(gene + bit));
//		}
//
//		directions.push_back(binToInt(currentGene));
//	}
//
//	return directions;
//}
//
////vector<int> NNGenAlg::decode(const vector<double> &bits) {
////
////}
//
//void NNGenAlg::calculateNotableScores() {
//	totalFitnessScore = 0;
//
//	double highest = 0;
//	double lowest = 99999;
//
//	for (int i = 0; i < popSize; i++) {
//		//update fittest
//		if (population[i].fitness > highest) {
//			highest = population[i].fitness;
//			fittestGenome = i;
//			bestFitnessScore = highest;
//		}
//
//		//update worst
//		if (population[i].fitness < lowest) {
//			lowest = population[i].fitness;
//			worstFitnessScore = lowest;
//		}
//
//		totalFitnessScore += population[i].fitness;
//	}
//
//	averageFitnessScore = totalFitnessScore / popSize;
//}
//int NNGenAlg::binToInt(const vector<int> &v) {
//	int value = 0;
//	int multiplier = 1;
//
//	for (int bit = v.size(); bit > 0; bit--) {
//		value += v.at(bit - 1) * multiplier;
//
//		multiplier *= 2;
//	}
//
//	return value;
//}
//
//void NNGenAlg::createStartPopulation() {
//	population.clear();
//
//	for (int i = 0; i < popSize; i++) {
//		GLfloat r = randFloat();
//		GLfloat g = randFloat();
//		GLfloat b = randFloat();
//		population.push_back(Genome(chromLength, r, g, b));
//	}
//
//	//set all stats to 0
//	generation = 0;
//	fittestGenome = 0;
//	bestFitnessScore = 0;
//	totalFitnessScore = 0;
//}
//
//
//void NNGenAlg::epoch() {
//	updateFitnessScores();
//
//	//create a new population
//	int genomeAmt = 0;
//
//	//vector of new genomes
//	vector<Genome> newGenomes;
//
//	while (genomeAmt < popSize) {
//		//get 2 parents
//		Genome mom = selection();
//		Genome dad = selection();
//
//		//crossover
//		Genome baby1, baby2;
//		crossover(mom.chromosome, dad.chromosome, baby1.chromosome, baby2.chromosome);
//
//		//mutate
//		mutate(baby1.chromosome);
//		mutate(baby2.chromosome);
//
//		//add to new population
//		newGenomes.push_back(baby1);
//		newGenomes.push_back(baby2);
//
//		genomeAmt += 2;
//	}
//
//	//copy children into original population
//	population = newGenomes;
//
//	//new generation created
//	++generation;
//}
//
//int NNGenAlg::currentGeneration() {
//	return generation;
//}
//
//int NNGenAlg::getFittestGenome() {
//	return fittestGenome;
//}
