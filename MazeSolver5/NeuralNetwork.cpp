#include "NeuralNetwork.h"

Neuron::Neuron(int nInputs) : numInputs(nInputs + 1) {
	for (int i = 0; i < numInputs + 1; i++) {
		weights.push_back(randomClamped());
	}
}

NeuronLayer::NeuronLayer(int numNeurons, int numInputsPerNeuron) :
	numNeurons(numNeurons) {
	for (int i = 0; i < numNeurons; i++) {
		neurons.push_back(Neuron(numInputsPerNeuron));
	}
}

NeuralNetwork::NeuralNetwork()
{
	numInputs = 4;
	numOutputs = 4;
	numHiddenLayers = 1;
	hiddenNeurons = 10;
	bias = -1;
	activationResponse = 1;
	createNetwork();
}


void NeuralNetwork::createNetwork() {
	//create the layers
	if (numHiddenLayers > 0) {
		//first hidden layer
		layers.push_back(NeuronLayer(hiddenNeurons, numInputs));

		for (int i = 0; i < numHiddenLayers - 1; i++) {
			layers.push_back(NeuronLayer(hiddenNeurons, hiddenNeurons));
		}

		//output layer
		layers.push_back(NeuronLayer(numOutputs, hiddenNeurons));
	}

	else {
		layers.push_back(NeuronLayer(numOutputs, numInputs));
	}
}

//replace the weights with new values
void NeuralNetwork::replaceWeights(vector<double> &weights) {
	int weight = 0;

	for (int i = 0; i < numHiddenLayers + 1; i++) {
		for (int j = 0; j < layers[i].numNeurons; j++) {
			for (int k = 0; k < layers[i].neurons[j].numInputs; k++) {
				layers[i].neurons[j].weights[k] = weights[weight++];
			}
		}
	}

	return;
}

int NeuralNetwork::getNumberWeights() const {
	int weights = 0;

	for (int i = 0; i < numHiddenLayers + 1; i++) {
		for (int j = 0; j < layers[i].numNeurons; j++) {
			for (int k = 0; k < layers[i].neurons[j].numInputs; k++) {
				weights++;
			}
		}
	}

	return weights;
}

//splits the weights for 2 point crossover in genetic algorithm
vector<int> NeuralNetwork::calculateSplitPoints() const {
	vector<int> splitPoints;

	int weightCounter = 0;

	for (int i = 0; i < numHiddenLayers + 1; i++) {
		for (int j = 0; j < layers[i].numNeurons; j++) {
			for (int k = 0; k < layers[i].neurons[j].numInputs; k++) {
				weightCounter++;
			}
			splitPoints.push_back(weightCounter - 1);
		}
	}
	return splitPoints;
}

vector<double> NeuralNetwork::update(vector<double> &inputs) {
	//resulting outputs from each layer
	vector<double> outputs;

	int weight = 0;

	//check for correct amount of inputs
	if (inputs.size() != numInputs) {
		return outputs;
	}

	for (int i = 0; i < numHiddenLayers + 1; i++) {
		if (i > 0) {
			inputs = outputs;
		}

		outputs.clear();

		weight = 0;

		//for each neuron, sum the inputs and weights
		//then calculate the total using activation function
		for (int j = 0; j < layers[i].numNeurons; j++) {
			double netInput = 0;

			int numInputs = layers[i].neurons[j].numInputs;

			for (int k = 0; k < numInputs - 1; k++) {
				netInput += layers[i].neurons[j].weights[k] * inputs[weight++];
			}

			//add in bias
			netInput += layers[i].neurons[j].weights[numInputs - 1] * bias;

			outputs.push_back(sigmoid(netInput, activationResponse));

			weight = 0;
		}
	}

	return outputs;
}

double NeuralNetwork::sigmoid(double netInput, double response) {
	return ( 1 / (1 + exp(-netInput / response)));
}