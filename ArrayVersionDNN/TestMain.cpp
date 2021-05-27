#include "NeuralNetwork.h"
#include "ActivationFunctions.h"
int main(){
	int neuronCount[2] = {3, 3};
	float(*ActFunc[3])(float x) = { LinearFunc,Sigmoid,Sigmoid};
	float(*ActFuncGrad[3])(float x) = { LinearFuncGradient,SigmoidPrime,SigmoidPrime};
	float bias[3] = { 0.0f, 0.0f, 0.0f};
	float input[2] = { 1.0f, 1.0f };
	float answer[2] = { 0.5f, 1.0f };
	neuralNetwork<float> Net(neuronCount, sizeof(neuronCount) / sizeof(int), bias, sizeof(bias) / sizeof(float), ActFunc, sizeof(ActFunc) / sizeof(float(*)(float x)), ActFuncGrad, sizeof(ActFunc) / sizeof(float(*)(float x)), answer, sizeof(answer) / sizeof(float), input, sizeof(input) / sizeof(float), sizeof(neuronCount) / sizeof(int), 0.1f);
	for (int i = 0; i < 1; i++) {
		//Net.PrintAllLayer();
		Net.FeedForward();
		Net.BackPropogation();
	}
	Net.FeedForward();
	//Net.PrintAllLayer();


	return 0;
}

