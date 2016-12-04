#pragma once
#include <vector>
#include "utility.h"

struct Neuron {
	//number of inputs
	int numInputs;

	//weights
	vector<double> weights;

	Neuron(int nInputs);
};

struct NeuronLayer {
	int numNeurons;
	vector<Neuron> neurons;  //the layer of neurons

	NeuronLayer(int numNeurons, int numInputsPerNeuron);
};

class NeuralNetwork
{
private:
	int numInputs;
	int numOutputs;
	int numHiddenLayers;
	int hiddenNeurons;  //number of neurons per hidden layer

	//vector for neuron layers
	vector<NeuronLayer> layers;

public:
	double bias;
	double activationResponse;

	NeuralNetwork();

	void createNetwork();
	vector<double> getWeights() const;
	int getNumberWeights() const;
	//replace weights
	void replaceWeights(vector<double> &weights);
	//calculate outputs from set of inputs
	vector<double> update(vector<double> &inputs);

	//calculates all points in the weight vector wich represent
	//the start and end points of neurons
	vector<int> calculateSplitPoints() const;

	//sigmoid function
	inline double sigmoid(double activation, double response);
};

