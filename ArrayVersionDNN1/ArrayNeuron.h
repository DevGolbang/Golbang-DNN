#pragma once
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <cassert>
#include <iostream>
using namespace std;
float LinearFunc(float x) {
	return x;
}
template <typename T1>
class Neuron
{
public:
	Neuron() {

	}
	~Neuron() {

	}
	void SetBias(T1 Bias) {
		bias = Bias;
	}
	void SetActiveFunc(T1(*pActivefunc)(T1 x)) {
		pActiveFunc = pActivefunc;
	}
	void InitInputsFromIn(T1 inputs[]) {
		InputsFromIn = inputs;
	}
	void InitWeighsFromIn(int _WeighsFromInCount) {
		WeighsFromIn = new T1[_WeighsFromInCount];
		for (int i = 0; i < _msize(WeighsFromIn) / sizeof(*WeighsFromIn); i++) {
			srand((unsigned int)time(NULL));
			WeighsFromIn[i] = (T1)(rand() % 10);

			Sleep(1000);
		}
	}
	void FeedForward() {
		T1 WeighSum = 0;
		cout << "가중합: ";
		for (int i = 0; i < _msize(WeighsFromIn) / sizeof(T1); i++) {
			WeighSum += WeighsFromIn[i] * InputsFromIn[i];
			cout << WeighsFromIn[i] << " X " << InputsFromIn[i] << "+";
		}
		cout << bias << endl;
		Output = (*pActiveFunc)(WeighSum + bias);
	}
	T1 Output = 0;
private:
	T1* WeighsFromIn;
	int WeighsFromInCount;
	T1* WeighsFromOut;
	int WeighsFromOutCount;
	T1(*pActiveFunc)(T1 x);
	T1* InputsFromIn;
	T1 bias;

};

template <typename T2>
class Layer {
public:
	Layer() {
		neurons = new Neuron
	}
	~Layer() {

	}
	int GetNeuronCount() {
		return NeuronCount;
	}
	void InitNeuron(int neuronCount) {
		NeuronCount = neuronCount;

	}
	void SetInputsFromIn() {
		for (int i = 0; i < pPrevLayer->NeuronCount; i++) {
			InputsFromIn[i] = pPrevLayer->neurons[i].Output;
			cout << "이전 결과값 : " << pPrevLayer->neurons[i].Output << endl;
		}

	}

	void SetBias(T2 _bias) {
		Bias = _bias;
		for (int i = 0; i < NeuronCount; i++) {
			neurons[i].SetBias(Bias);
		}
	}
	void SetActiveFunc(T2(*_pActFunc)(T2 x)) {
		pActFunc = _pActFunc;
		for (int i = 0; i < NeuronCount; i++) {
			neurons[i].SetActiveFunc(pActFunc);
		}
	}

	void InitInputsFromIn() {
		InputsFromIn = new T2[pPrevLayer->NeuronCount];
		for (int i = 0; i < NeuronCount; i++) {
			neurons[i].InitInputsFromIn(InputsFromIn);

		}
	}
	void InitWeighsFromIn() {
		for (int i = 0; i < NeuronCount; i++) {

			neurons[i].InitWeighsFromIn(pPrevLayer->NeuronCount);
		}
	}
	void FeedForward() {

		for (int i = 0; i < NeuronCount; i++) {

			neurons[i].FeedForward();
		}


	}
	Layer<T2>* pPrevLayer = nullptr, * pNextLayer = nullptr;
	Neuron<T2>* neurons;
private:

	T2* InputsFromIn;
	T2(*pActFunc)(T2 x) = nullptr;
	int NeuronCount = 0;
	T2 Bias = 0;
};
template <typename T3>
class neuralNetwork {
public:
	neuralNetwork(int NeuronCounts[],int NeuronCountsCount, T3 BiasGroup[], int BiasGroupCount,T3(*ActFuncMass[])(T3 x), int ActFuncCount, T3 answer[], int AnswerCount, T3 input[], int InputCount, int layerCount, T3 _Learningconst) {
		InitHiddenLayers(layerCount, NeuronCounts);
		SetHiddenLayersNeuronCounts(NeuronCounts, NeuronCountsCount);
		InitInputLayer(input, InputCount);
		InitAnswerLayer(answer, AnswerCount);
		SetInputLayer(input);
		SetAnswerLayer(answer);
		ConnectHiddenLayersAndIOLayers();
		SetBiasGroup(BiasGroup, BiasGroupCount);
		SetActivationFunc(ActFuncMass, ActFuncCount);
		InitInputsFromIn();
		InitWeighsFromIn();
		LearningConst = _Learningconst;
	}
	~neuralNetwork() {

	}
	void InitInputsFromIn() {
		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers[i].InitInputsFromIn();



		}
	}
	void SetInputsFromIn() {
		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers[i].SetInputs();
		}
	}
	void InitHiddenLayers(int _layerCount, int NeuronCount[]) {
		HiddenLayerCount = _layerCount;
		HiddenLayers = new Layer<T3>[HiddenLayerCount];
		for (int i = 0; i < HiddenLayerCount; i++) {
			Layer<T3> temp;
			temp.neurons = new Neuron<T3>[NeuronCount[i]];
			HiddenLayers[i] = temp;
		}
	}
	void InitInputLayer(T3 input[], int count) {
		InputLayer = new Layer<T3>();
		InputLayer->neurons = new Neuron<T3>[count];
		

	}
	void InitAnswerLayer(T3 answer[], int count) {
		AnswerLayer = new Layer<T3>();
		AnswerLayer->neurons = new Neuron<T3>[count];
	}
	void SetInputLayer(T3 input[]) {

		InputLayer->InitNeuron(count);
		InputLayer->pNextLayer = &HiddenLayers[0];
		for (int i = 0; i < count; i++) {
			InputLayer->neurons[i].Output = input[i];
		}
	}
	void SetAnswerLayer(T3 answer[]) {
		AnswerLayer->InitNeuron(count);
		AnswerLayer->pPrevLayer = &HiddenLayers[HiddenLayerCount - 1];
		for (int i = 0; i < count; i++) {
			AnswerLayer->neurons[i].Output = answer[i];
		}
	}
	void SetHiddenLayersNeuronCounts(int NeuronCount[], int count) {
		if (HiddenLayerCount != count) {
			cout << "노드숫자 배열 개수와 레이어 수가 다릅니다. " << endl;
			for (int i = 0; i < count; i++) {
				cout << NeuronCount[i] << endl;
			}
			return;
		}

		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers[i].InitNeuron(NeuronCount[i]);
		}
	}
	void SetBiasGroup(T3 BiasGroup[], int count) {
		if (HiddenLayerCount != count) {
			cout << "bias 개수와 레이어 수가 다릅니다. " << count << "개" << endl;
			for (int i = 0; i < count; i++) {
				cout << BiasGroup[i] << endl;
			}
			return;
		}
		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers[i].SetBias(BiasGroup[i]);
		}
	}
	void SetActivationFunc(T3(*ActFuncMass[])(T3 x), int count ) {
		if (HiddenLayerCount != count) {
			cout << "활성화 함수 개수와 레이어 수가 다릅니다. " << endl;
			return;
		}
		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers[i].SetActiveFunc(ActFuncMass[i]);
		}
	}
	void ConnectHiddenLayersAndIOLayers() {
		Layer<T3>* pLayerConnector;
		for (int i = 0; i < HiddenLayerCount; i++) {
			pLayerConnector = &HiddenLayers[i];
			if (i == 0) {
				pLayerConnector->pPrevLayer = InputLayer;
				pLayerConnector->pNextLayer = &HiddenLayers[i + 1];
			}
			else if (i == HiddenLayerCount - 1) {
				pLayerConnector->pPrevLayer = &HiddenLayers[i - 1];
				pLayerConnector->pNextLayer = AnswerLayer;
			}
			else {
				pLayerConnector->pPrevLayer = &HiddenLayers[i - 1];
				pLayerConnector->pNextLayer = &HiddenLayers[i + 1];
			}

		}
	}
	void InitWeighsFromIn() {
		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers[i].InitWeighsFromIn();
		}
	}
	void FeedForward() {
		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers[i].SetInputsFromIn();
			HiddenLayers[i].FeedForward();

		}
	}
	void PrintAllLayer() {
		Layer<T3>* LayerExplorer = InputLayer;
		for (int i = 0; i < HiddenLayerCount + 2; i++) {
			for (int k = 0; k < LayerExplorer->GetNeuronCount(); k++) {
				cout << LayerExplorer->neurons[k].Output << " ";
			}
			cout << endl;
			LayerExplorer = LayerExplorer->pNextLayer;
		}
	}
private:
	Layer<T3>* HiddenLayers;
	Layer<T3>* InputLayer, * AnswerLayer;
    int* HiddenLayerNeuronCounts;
	int HiddenLayerCount;
	T3 LearningConst;
};

