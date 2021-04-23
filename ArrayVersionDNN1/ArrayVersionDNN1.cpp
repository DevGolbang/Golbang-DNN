

#include "ArrayNeuron.h"

int main()
{
	int nodeCount[3] = { 2,3,4 };
	float(*ActFunc[3])(float x) = { LinearFunc,LinearFunc,LinearFunc };
	float bias[3] = {0.0f, 0.0f, 0.0f };
	float input[3] = { 1.0f, 1.0f, 1.0f };
	float answer[3] = { 1.0f, 1.0f, 1.0f };
	neuralNetwork<float> Net(nodeCount, sizeof(nodeCount) / sizeof(int),bias,sizeof(bias) / sizeof(float) ,ActFunc, sizeof(ActFunc) / sizeof(float(*)(float x)),answer, sizeof(answer) / sizeof(float),input, sizeof(input) / sizeof(float),3, 0.1f);
    Net.FeedForward();
	Net.PrintAllLayer();
	return 0;
}



