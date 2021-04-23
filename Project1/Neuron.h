#pragma once
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <cassert>
#include "LinkedList.h"
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
	void InitInputsFromIn(List<T1>* inputs) {
		InputsFromIn = inputs;
	}
	void InitWeighsFromIn() {
		for (int i = 0; i < InputsFromIn->GetNodeCount(); i++) {
			srand((unsigned int)time(NULL));
			WeighsFromIn.InsertLast((T1)(rand() % 40));

			Sleep(1000);
		}
	}
	void FeedForward() {
		T1 WeighSum = 0;
		cout << "가중합: ";
		for (int i = 0; i < WeighsFromIn.GetNodeCount(); i++) {
			WeighSum += (*(WeighsFromIn.FindByIndex(i))) * (*(InputsFromIn->FindByIndex(i)));
			cout  <<*(WeighsFromIn.FindByIndex(i)) << " X " << *(InputsFromIn->FindByIndex(i))  << "+" << endl;
		}
		cout << bias << endl;
		Output = (*pActiveFunc)(WeighSum + bias);
	}
	T1 Output = 0;
private:
	List<T1> WeighsFromIn;
	T1(*pActiveFunc)(T1 x);
	List<T1>* InputsFromIn;
	T1 bias;

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
		for (int i = 0; i < pPrevLayer->neurons.GetNodeCount(); i++) {
			InputsFromIn[i] = pPrevLayer->neurons.FindByIndex(i)->Output;
			cout << "이전 결과값 : " << pPrevLayer->neurons.FindByIndex(i)->Output << endl;
		}

	}

	void SetBias(T2 _bias) {
		Bias = _bias;
		for (int i = 0; i < neurons.GetNodeCount(); i++) {
			neurons.FindByIndex(i)->SetBias(Bias);
		}
	}
	void SetActiveFunc(T2(*_pActFunc)(T2 x)) {
		pActFunc = _pActFunc;
		for (int i = 0; i < neurons.GetNodeCount(); i++) {
			neurons.FindByIndex(i)->SetActiveFunc(pActFunc);
		}
	}

	void InitInputsFromIn() {
		
		for (int i = 0; i < pPrevLayer->neurons.GetNodeCount(); i++) {
				InputsFromIn.InsertLast(NULL);
		}
		for (int i = 0; i < neurons.GetNodeCount(); i++) {
		neurons.FindByIndex(i)->InitInputsFromIn(&InputsFromIn);

	     }
       }
	void InitWeighsFromIn() {
		for (int i = 0; i < neurons.GetNodeCount(); i++) {

				neurons.FindByIndex(i)->InitWeighsFromIn();
		}
	}
	void FeedForward() {

		for (int i = 0; i < neurons.GetNodeCount(); i++) {
			
			neurons.FindByIndex(i)->FeedForward();
		}
		

	}
	Layer<T2>* pPrevLayer = nullptr, * pNextLayer = nullptr;
	List<Neuron<T2>> neurons;
private:

	List<T2> InputsFromIn;
	T2(*pActFunc)(T2 x) = nullptr;
	int NeuronCount = 0;
	T2 Bias = 0;
 };
template <typename T3>
class neuralNetwork {
public:
	neuralNetwork(List<int>* NeuronCount, List<T3>* BiasGroup, List<T3(*)(T3 x)>* ActFuncMass, List<T3> *answer, List<T3> *input,int layerCount, T3 _Learningconst) {
		InitHiddenLayers(layerCount, NeuronCount);
		SetNeuronCounts(NeuronCount);
		InitInputLayer(input);
		InitAnswerLayer(answer);
		SetInputLayer(input);
		SetAnswerLayer(answer);
		ConnectHiddenLayersAndIOLayers();
		SetBiasGroup(BiasGroup);
		SetActivationFunc(ActFuncMass);
		InitInputsFromIn();
		InitWeighsFromIn();
		LearningConst = _Learningconst;
	}
	~neuralNetwork() {

	}
	void InitInputsFromIn() {
		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers.FindByIndex(i)->InitInputsFromIn();



		}
	}
	void SetInputsFromIn() {
		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers.FindByIndex(i)->SetInputs();
		}
	}
	void InitHiddenLayers(int _layerCount, List<int>* NeuronCount) {
		HiddenLayerCount = _layerCount;
		for (int i = 0; i < HiddenLayerCount; i++) {
			Layer<T3> temp;
			for (int k = 0; k < *(NeuronCount->FindByIndex(i)); k++) {
				Neuron<T3> tmp;
				temp.neurons.InsertLast(tmp);
			}
			HiddenLayers.InsertLast(temp);
		}
	}
	void InitInputLayer(List<T3>* input) {
		InputLayer = new Layer<T3>();
		for (int i = 0; i < input->GetNodeCount(); i++) {
			Neuron<T3> temp;
			InputLayer->neurons.InsertLast(temp);
		}
		
	}
	void InitAnswerLayer(List<T3>* answer) {
		AnswerLayer = new Layer<T3>();
		for (int i = 0; i < answer->GetNodeCount(); i++) {
			Neuron<T3> temp;
			AnswerLayer->neurons.InsertLast(temp);
		}
	}
	void SetInputLayer(List<T3> *input) {
		InputLayer->InitNeuron(input->GetNodeCount());
		InputLayer->pNextLayer = &HiddenLayers[0];
		for (int i = 0; i < input->GetNodeCount(); i++) {
			InputLayer->neurons.FindByIndex(i)->Output = *(input->FindByIndex(i));
		}
	}
	void SetAnswerLayer(List<T3> *answer) {
		AnswerLayer->InitNeuron(answer->GetNodeCount());
		AnswerLayer->pPrevLayer = &HiddenLayers[HiddenLayerCount - 1];
		for (int i = 0; i < answer->GetNodeCount(); i++) {
			AnswerLayer->neurons.FindByIndex(i)->Output = *(answer->FindByIndex(i));
		}
	}
	void SetNeuronCounts(List<int> *NeuronCount) {
		if (HiddenLayerCount != NeuronCount->GetNodeCount()) {
			cout << "노드숫자 배열 개수와 레이어 수가 다릅니다. " << endl;
			for (int i = 0; i < NeuronCount->GetNodeCount(); i++) {
				cout << *(NeuronCount->FindByIndex(i)) << endl;
			}
			return;
		}
	
		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers.FindByIndex(i)->SetNeuronCount(*(NeuronCount->FindByIndex(i)));
		}
	}
	void SetBiasGroup(List<T3>* BiasGroup) {
		if (HiddenLayerCount != BiasGroup->GetNodeCount()) {
			cout << "bias 개수와 레이어 수가 다릅니다. " << BiasGroup->GetNodeCount()  << "개"<< endl;
			for (int i = 0; i < BiasGroup->GetNodeCount(); i++) {
				cout << *(BiasGroup->FindByIndex(i)) << endl;
			}
			return;
		}
		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers.FindByIndex(i)->SetBias(*(BiasGroup->FindByIndex(i)));
		}
	}
	void SetActivationFunc(List<T3(*)(T3 x)>* ActFuncMass) {
		if (HiddenLayerCount != ActFuncMass->GetNodeCount()) {
			cout << "활성화 함수 개수와 레이어 수가 다릅니다. " << endl;
			return;
		}
		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers.FindByIndex(i)->SetActiveFunc(*(ActFuncMass->FindByIndex(i)));
		}
	}
	void ConnectHiddenLayersAndIOLayers() {
		Layer<T3>* pLayerConnector;
		for (int i = 0; i < HiddenLayers.GetNodeCount(); i++) {
			pLayerConnector = &HiddenLayers[i];
			if (i == 0) {
				pLayerConnector->pPrevLayer = InputLayer;
				pLayerConnector->pNextLayer = &HiddenLayers[i + 1];
			}
			else if (i == HiddenLayers.GetNodeCount() - 1) {
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
			HiddenLayers.FindByIndex(i)->InitWeighsFromIn();
		}
	}
	void FeedForward() {
		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers.FindByIndex(i)->SetInputsFromIn();
			HiddenLayers.FindByIndex(i)->FeedForward();

		}
	}
	void PrintAllLayer() {
		Layer<T3>* LayerExplorer = InputLayer;
		for (int i = 0; i < HiddenLayerCount + 2; i++) {
			for (int k = 0; k < LayerExplorer->GetNeuronCount(); k++) {
				cout << LayerExplorer->neurons.FindByIndex(k)->Output << " ";
			 }
			cout << endl;
			LayerExplorer = LayerExplorer->pNextLayer;
		}
	}
private:
	List<Layer<T3>> HiddenLayers;
	Layer<T3> *InputLayer, *AnswerLayer;
	List<int> HiddenLayerNeuronCounts;
	int HiddenLayerCount;
	T3 LearningConst;
};

