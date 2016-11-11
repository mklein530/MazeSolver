#pragma once
#include <random>

using namespace std;

#define CROSSOVER_RATE 0.7
#define MUTATION_RATE 0.001
#define POP_SIZE 100
#define CHROM_LENGTH 70

//returns a random integer between x and y
inline int	  randInt(int x, int y) { return rand() % (y - x + 1) + x; }

//returns a random float between zero and 1
inline double randFloat() { return (rand()) / (RAND_MAX + 1.0); }

//returns a random bool
inline bool   randBool()
{
	if (randInt(0, 1)) return true;

	else return false;
}

//returns a random float in the range -1 < n < 1
inline double randomClamped() { return randFloat() - randFloat(); }


