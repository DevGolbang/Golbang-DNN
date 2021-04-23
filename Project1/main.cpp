
#include "Neuron.h"


int main() {
	List<int> nodeCount;
	nodeCount.InsertLast(2);
	nodeCount.InsertLast(2);
	nodeCount.InsertLast(2);
	List<float(*)(float x)> ActFunc;
	ActFunc.InsertLast(LinearFunc);
	ActFunc.InsertLast(LinearFunc);
	ActFunc.InsertLast(LinearFunc);
	List<float> bias;
	bias.InsertLast(0.0f);
	bias.InsertLast(0.0f);
	bias.InsertLast(0.0f);
	List<float> input;
	input.InsertLast(1.0f);
	input.InsertLast(1.0f);
	input.InsertLast(1.0f);
	List<float> answer;
	answer.InsertLast(1.0f);
	answer.InsertLast(1.0f);
	answer.InsertLast(1.0f);
	neuralNetwork<float> Net(&nodeCount, &bias, &ActFunc, &answer, &input, 3, 0.1f);
	Net.FeedForward();
	Net.PrintAllLayer();
	return 0;
}

