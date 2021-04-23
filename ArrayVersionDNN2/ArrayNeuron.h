#pragma once
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <cassert>
#include <iostream>
#include <cmath>
using namespace std;
float Sigmoid(float x) {
	return 1.0f / (1.0f + exp(-x));
}
float SigmoidPrime(float x) {
	return Sigmoid(x) * (1.0f - Sigmoid(x));
}
float LinearFunc(float x) {
	return x;
}
float LinearFuncGradient(float x) {
	return 1.0f;
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
	void SetLearningConst(T1 _learningConst) {
		LearningConst = _learningConst;
	}
	void SetActiveFunc(T1(*pActivefunc)(T1 x)) {
		pActiveFunc = pActivefunc;
	}
	void SetActiveFuncGradient(T1(*pActivefuncGradient)(T1 x)) {
		pActiveFuncGradient = pActivefuncGradient;
	}
	void InitInputsFromIn(T1 inputs[]) {
		InputsFromIn = inputs;
	}
	void SetDeltasFromOut(T1 deltas[]) {
		DeltasFromOut = deltas;
	}
	void InitWeighsFromIn(int _WeighsFromInCount) {
		WeighsFromInCount = _WeighsFromInCount;
		WeighsFromIn = new T1[WeighsFromInCount];
		for (int i = 0; i < _msize(WeighsFromIn) / sizeof(T1); i++) {
			WeighsFromIn[i] = 1.0f;
		}
	}
	void SetWeighsFromOut(T1* _WeighsFromOut[], int _WeighsFromOutCount) {
		WeighsFromOut = _WeighsFromOut;
		WeighsFromOutCount = _WeighsFromOutCount;
	}
	void FeedForward() {
		WeighSum = 0;
		//cout << "앞먹임 가중합: ";
		for (int i = 0; i < _msize(WeighsFromIn) / sizeof(T1); i++) {
			WeighSum += WeighsFromIn[i] * InputsFromIn[i];
			//cout << WeighsFromIn[i] << " X " << InputsFromIn[i] << " + ";
		}
		//cout << bias << endl;
		Output = pActiveFunc(WeighSum) + bias;
	}
	void BackPropWeighsFromIn() {
		for (int i = 0; i < WeighsFromInCount; i++) {
			//cout << " OutputDelta: " <<  OutputDelta << endl;
			WeighsFromIn[i] += LearningConst * OutputDelta * InputsFromIn[i];
		}
	}

	void BackPropogation() {
		Error = 0;
		for (int i = 0; i < _msize(DeltasFromOut) / sizeof(T1); i++) {
			Error += (*(WeighsFromOut[i])) * DeltasFromOut[i];
		
			}

		OutputDelta = pActiveFuncGradient(WeighSum) * Error;
		//cout << "오차 : " << OutputDelta << endl;

	}
	void BackPropogation(T1 _error) {
		Error = _error;
		OutputDelta = pActiveFuncGradient(WeighSum) * Error;
		//cout << "입력값 - 정답형 오차 : " << OutputDelta << endl;
	}
	T1 Output = 0;
	T1 OutputDelta = 0;
	T1 Error = 0;
	T1* WeighsFromIn;
private:
	T1 WeighSum = 0;
	int WeighsFromInCount;
	T1** WeighsFromOut;
	int WeighsFromOutCount;
	T1(*pActiveFunc)(T1 x);
	T1(*pActiveFuncGradient)(T1 x);
	T1* InputsFromIn;
	T1* DeltasFromOut;
	T1 bias;
	T1 LearningConst;
};

template <typename T2>
class Layer {
public:
	Layer() {

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
			//cout << "이전 결과값 : " << pPrevLayer->neurons[i].Output << endl;
		}

	}

	void SetBias(T2 _bias) {
		Bias = _bias;
		for (int i = 0; i < NeuronCount; i++) {
			neurons[i].SetBias(Bias);
		}
	}

	void SetLearningConst(T2 _learningConst) {
		learningConst = _learningConst;
		for (int i = 0; i < NeuronCount; i++) {
			neurons[i].SetLearningConst(learningConst);
		}
	}
	void SetActiveFunc(T2(*_pActFunc)(T2 x)) {
		pActFunc = _pActFunc;
		for (int i = 0; i < NeuronCount; i++) {
			neurons[i].SetActiveFunc(pActFunc);
		}
	}
	void SetActiveFuncGradient(T2(*_pActFuncGrad)(T2 x)) {
		pActFuncGradient = _pActFuncGrad;
		for (int i = 0; i < NeuronCount; i++) {
			neurons[i].SetActiveFuncGradient(pActFuncGradient);
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
	void SetWeighsFromOut() {
		T2*** temp = new T2 **[NeuronCount];
		for (int j = 0; j < NeuronCount; j++) {
			temp[j] = new T2*[pNextLayer->NeuronCount];
		}

		for (int i = 0; i < NeuronCount; i++) {
			for (int k = 0; k < pNextLayer->NeuronCount; k++) {
				temp[i][k] = &(pNextLayer->neurons[k].WeighsFromIn[i]);
			}
			neurons[i].SetWeighsFromOut(temp[i] , pNextLayer->NeuronCount);
		}
	}
	void SetIsOutputOrNot(bool _IsOutput) {
		IsOutputLayer = _IsOutput;
	}
	void SetDeltasFromOut() {
		T2* temp = new T2[pNextLayer->NeuronCount];
		for (int i = 0; i < pNextLayer->NeuronCount; i++) {
			temp[i] = pNextLayer->neurons[i].OutputDelta;
		}
		for (int i = 0; i < NeuronCount; i++) {
			neurons[i].SetDeltasFromOut(temp);
          }
	}
	void FeedForward() {
		for (int i = 0; i < NeuronCount; i++) {
			neurons[i].FeedForward();
		}
	}
	void BackPropWeighsFromOut() {
		for (int i = 0; i < NeuronCount; i++) {
			neurons[i].BackPropWeighsFromIn();
		}
	}
	void BackPropogation() {
		if (IsOutputLayer) {
			for (int i = 0; i < NeuronCount; i++) {
				neurons[i].BackPropogation(pNextLayer->neurons[i].Output - neurons[i].Output);
			}
			BackPropWeighsFromOut();
		}
		else {
			SetWeighsFromOut();
			SetDeltasFromOut();
			for (int i = 0; i < NeuronCount; i++) {
				neurons[i].BackPropogation();
			}
			BackPropWeighsFromOut();
		}
	
	}
	Layer<T2>* pPrevLayer = nullptr, * pNextLayer = nullptr;
	Neuron<T2>* neurons;
private:
	bool IsOutputLayer = false;
	T2* InputsFromIn = nullptr;
	T2(*pActFunc)(T2 x) = nullptr;
	T2(*pActFuncGradient)(T2 x) = nullptr;
	int NeuronCount = 0;
	T2 Bias = 0;
	T2 learningConst = 0;
};
template <typename T3>
class neuralNetwork {
public:
	neuralNetwork(int NeuronCounts[], int NeuronCountsCount, T3 BiasGroup[], int BiasGroupCount, T3(*ActFuncMass[])(T3 x), int ActFuncCount, T3(*ActFuncGradMass[])(T3 x), int ActFuncGradientCount, T3 answer[], int AnswerCount, T3 input[], int InputCount, int layerCount, T3 _Learningconst) {
		InitHiddenLayers(layerCount, NeuronCounts);
		SetHiddenLayersNeuronCounts(NeuronCounts, NeuronCountsCount);
		InitInputLayer(input, InputCount);
		InitAnswerLayer(answer, AnswerCount);
		SetInputLayer(input);
		SetAnswerLayer(answer);
		SetOutputLayer();
		ConnectHiddenLayersAndIOLayers();
		SetBiasGroup(BiasGroup, BiasGroupCount);
		SetLearningConst(_Learningconst);
		SetActivationFunc(ActFuncMass, ActFuncCount);
		SetActivationFuncGradient(ActFuncGradMass, ActFuncGradientCount);
		InitInputsFromIn();
		InitWeighsFromIn();
	}
	~neuralNetwork() {

	}
	void InitInputsFromIn() {
		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers[i].InitInputsFromIn();
		}
		OutputLayer.InitInputsFromIn();
	}
	void SetInputsFromIn() {
		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers[i].SetInputsFromIn();
		}
		OutputLayer.SetInputsFromIn();
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
		InputLayerNeuronCount = count;
		InputLayer = new Layer<T3>();
		InputLayer->neurons = new Neuron<T3>[InputLayerNeuronCount];


	}
	void InitAnswerLayer(T3 answer[], int count) {
		AnswerLayerNeuronCount = count;
		AnswerLayer = new Layer<T3>();
		AnswerLayer->neurons = new Neuron<T3>[AnswerLayerNeuronCount];
	}
	void SetInputLayer(T3 input[]) {
		InputLayer->InitNeuron(InputLayerNeuronCount);
		InputLayer->pNextLayer = &HiddenLayers[0];
		for (int i = 0; i < InputLayerNeuronCount; i++) {
			InputLayer->neurons[i].Output = input[i];
		}
	}
	void SetAnswerLayer(T3 answer[]) {
		AnswerLayer->InitNeuron(AnswerLayerNeuronCount);
		AnswerLayer->pPrevLayer = &OutputLayer;
		for (int i = 0; i < AnswerLayerNeuronCount; i++) {
			AnswerLayer->neurons[i].Output = answer[i];
		}
	}
	void SetOutputLayer() {
		OutputLayerNeuronCount = AnswerLayerNeuronCount;
		OutputLayer.InitNeuron(OutputLayerNeuronCount);
		OutputLayer.pPrevLayer = &HiddenLayers[HiddenLayerCount - 1];
		OutputLayer.pNextLayer = AnswerLayer;
		OutputLayer.SetIsOutputOrNot(true);
		OutputLayer.neurons = new Neuron<T3>[OutputLayerNeuronCount];
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
		if (HiddenLayerCount + 1!= count) {
			cout << "bias 개수와 레이어 수가 다릅니다. " << count << "개" << endl;
			for (int i = 0; i < count; i++) {
				cout << BiasGroup[i] << endl;
			}
			return;
		}
		cout << "bias 설정 중입니다."<< endl;
		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers[i].SetBias(BiasGroup[i]);
		}
		OutputLayer.SetBias(BiasGroup[HiddenLayerCount]);
		cout << "bias 설정이 완료되었습니다." << endl;
	}
	void SetLearningConst(T3 _learningConst) {
		cout << "교육 상수 설정 중입니다." << endl;
		LearningConst = _learningConst;
		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers[i].SetLearningConst(LearningConst);
		}
		OutputLayer.SetLearningConst(LearningConst);
		cout << "교육 상수 설정이 완료되었습니다." << endl;
	}
	void SetActivationFunc(T3(*ActFuncMass[])(T3 x), int count) {
		if (HiddenLayerCount + 1!= count) {
			cout << "활성화 함수 개수와 레이어 수가 다릅니다. " << endl;
			return;
		}
		cout << "활성화 함수 설정 중입니다." << endl;
		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers[i].SetActiveFunc(ActFuncMass[i]);
		}
		OutputLayer.SetActiveFunc(ActFuncMass[HiddenLayerCount]);
		cout << "활성화 함수 설정이 완료되었습니다." << endl;
	}
	void SetActivationFuncGradient(T3(*ActFuncGradMass[])(T3 x), int count) {
		if (HiddenLayerCount + 1 != count) {
			cout << "활성화 함수의 도함수 개수와 레이어 수가 다릅니다. " << endl;
			return;
		}
		cout << "활성화 함수의 도함수를 설정 중입니다." << endl;
		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers[i].SetActiveFuncGradient(ActFuncGradMass[i]);
		}
		OutputLayer.SetActiveFuncGradient(ActFuncGradMass[HiddenLayerCount]);
		cout << "활성화 함수의 도함수가 설정 완료되었습니다." << endl;
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
				pLayerConnector->pNextLayer = &OutputLayer;
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
		OutputLayer.InitWeighsFromIn();
	}
	void FeedForward() {
		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers[i].SetInputsFromIn();
			HiddenLayers[i].FeedForward();
		}
		OutputLayer.SetInputsFromIn();
		OutputLayer.FeedForward();
	}
	void BackPropogation() {
		Layer<T3>* temp = &OutputLayer;
		while (temp->pPrevLayer != nullptr) {
			temp->BackPropogation();
				temp = temp->pPrevLayer;
		}
	
	}
	void PrintAllLayer() {
		Layer<T3>* LayerExplorer = InputLayer;
		for (int i = 0; i < HiddenLayerCount + 3; i++) {
			for (int k = 0; k < LayerExplorer->GetNeuronCount(); k++) {
				cout << LayerExplorer->neurons[k].Output << " ";
			}
			cout << endl;
			LayerExplorer = LayerExplorer->pNextLayer;
		}
	}
private:
	Layer<T3>* HiddenLayers;
	Layer<T3>* InputLayer, * AnswerLayer, OutputLayer;
	int* HiddenLayerNeuronCounts;
	int HiddenLayerCount;
	int InputLayerNeuronCount, OutputLayerNeuronCount, AnswerLayerNeuronCount;
	T3 LearningConst;
};

