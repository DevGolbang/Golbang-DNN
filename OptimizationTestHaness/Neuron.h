#pragma once
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <cassert>
#include "LinkedList.h"
float LinearFunc(float x) {
	return x;
}
float LinearFuncPrime(float x) {
	return 1;
}
template <typename T1>
class Neuron
{
public:
	Neuron() {

	}
	~Neuron() {

	}
	void SetLearningConst(T1 _learningconst) {
		LearningConst = _learningconst;
	}
	void SetBias(T1 Bias) {
		bias = Bias;
	}
	void SetActiveFunc(T1(*pActivefunc)(T1 x)) {
		pActiveFunc = pActivefunc;
	}
	void SetActiveFuncGradient(T1(*pActivefunc_prime)(T1 x)) {
		pActiveFuncGradient = pActivefunc_prime;
	}
	void InitInputsFromIn(List<T1>* inputs) {
		InputsFromIn = inputs;
	}
	void InitInputsFromOut(List<T1>* inputs) {
		InputsFromOut = inputs;
	}
	void InitWeighsFromIn() {
		for (int i = 0; i < InputsFromIn->GetNodeCount(); i++) {
			srand((unsigned int)time(NULL));
			WeighsFromIn.InsertLast((T1)(rand() % 40));

			Sleep(1000);
		}
	}
	void InitWeighsFromOut(List<T1>* Weighs) {
		WeighsFromOut = Weighs;
	}
	void SetWeighs() {
		for (int i = 0; i < WeighsFromOut->GetNodeCount(); i++) {
			(*(WeighsFromOut->FindByIndex(i))) = (*(WeighsFromOut->FindByIndex(i))) + LearningConst * (*pActiveFuncGradient)(WeighSum + bias) * Error;
		}

	}
	void FeedForward() {
		
		//cout << "가중합: ";
		for (int i = 0; i < WeighsFromIn.GetNodeCount(); i++) {
			WeighSum += (*(WeighsFromIn.FindByIndex(i))) * (*(InputsFromIn->FindByIndex(i)));
			//cout << *(WeighsFromIn.FindByIndex(i)) << " X " << *(InputsFromIn->FindByIndex(i)) << "+" << endl;
		}
		//cout << bias << endl;
		Output = (*pActiveFunc)(WeighSum + bias);
	}
	void BackPropogation() {
		
		for (int i = 0; i < WeighsFromIn.GetNodeCount(); i++) {
			cout << *(WeighsFromIn.FindByIndex(i)) << " X " << *(InputsFromIn->FindByIndex(i)) << "+" << endl;
		}
		cout << bias << endl;
		Output = (*pActiveFunc)(WeighSum + bias);
	}

	T1 Output = 0;
private:
	List<T1> WeighsFromIn;
	List<T1>* WeighsFromOut;
	T1(*pActiveFunc)(T1 x);
	T1(*pActiveFuncGradient)(T1 x);
	List<T1>* InputsFromIn;
	List<T1>* InputsFromOut;
	T1 bias;
	T1 Error;
	T1 LearningConst;
	T1 WeighSum = 0;

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
			//cout << "이전 결과값 : " << pPrevLayer->neurons.FindByIndex(i)->Output << endl;
		}

	}
	void SetInputsFromOut() {
		for (int i = 0; i < pNextLayer->neurons.GetNodeCount(); i++) {
			InputsFromOut[i] = pNextLayer->neurons.FindByIndex(i)->Output;
			//cout << "다음 결과값 : " << pNextLayer->neurons.FindByIndex(i)->Output << endl;
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
	void InitInputsFromOut() {

		for (int i = 0; i < pNextLayer->neurons.GetNodeCount(); i++) {
			InputsFromOut.InsertLast(NULL);
		}
		for (int i = 0; i < neurons.GetNodeCount(); i++) {
			neurons.FindByIndex(i)->InitInputsFromOut(&InputsFromOut);

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
	List<T2> InputsFromOut;
	T2(*pActFunc)(T2 x) = nullptr;
	int NeuronCount = 0;
	T2 Bias = 0;
	T2 LearningConst = 0;
};
template <typename T3>
class neuralNetwork {
public:
	neuralNetwork(List<int>* NeuronCount, List<T3>* BiasGroup, List<T3(*)(T3 x)>* ActFuncMass, List<T3>* answer, List<T3>* input, int layerCount, T3 _Learningconst, int OutputLayerNrnCnt) {
		InitHiddenLayers(layerCount, NeuronCount);
		SetNeuronCounts(NeuronCount);
		InitInputLayer(input);
		InitAnswerLayer(answer);
		SetInputLayer(input);
		SetAnswerLayer(answer);
		InitOutputLayer(OutputLayerNrnCnt);
		ConnectHiddenLayersAndIOLayers();
		SetBiasGroup(BiasGroup);
		SetActivationFunc(ActFuncMass);
		InitInputsFromIn();
		InitWeighs();
		LearningConst = _Learningconst;
	}
	~neuralNetwork() {

	}
	void InitInputsFromIn() {
		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers.FindByIndex(i)->InitInputsFromIn();

		}
		OutputLayer.InitInputsFromIn();
	}
	void SetInputsFromIn() {
		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers.FindByIndex(i)->SetInputsFromIn();
		}
		OutputLayer.SetInputsFromIn();
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
		
		for (int i = 0; i < input->GetNodeCount(); i++) {
			Neuron<T3> temp;
			InputLayer.neurons.InsertLast(temp);
		}

	}
	void InitAnswerLayer(List<T3>* answer) {
	
		for (int i = 0; i < answer->GetNodeCount(); i++) {
			Neuron<T3> temp;
			AnswerLayer.neurons.InsertLast(temp);
		}
	}
	void InitOutputLayer(int OutputCount) {
		for (int i = 0; i < OutputCount; i++) {
			Neuron<T3> temp;
			OutputLayer.neurons.InsertLast(temp);
		}
		OutputLayer.InitNeuron(OutputCount);
		OutputLayer.pPrevLayer = &HiddenLayers[HiddenLayerCount - 1];
	}
	void SetInputLayer(List<T3>* input) {
		InputLayer.InitNeuron(input->GetNodeCount());
		InputLayer.pNextLayer = &HiddenLayers[0];
		for (int i = 0; i < input->GetNodeCount(); i++) {
			InputLayer.neurons.FindByIndex(i)->Output = *(input->FindByIndex(i));
		}
	}
	void SetAnswerLayer(List<T3>* answer) {
		AnswerLayer.InitNeuron(answer->GetNodeCount());
		for (int i = 0; i < answer->GetNodeCount(); i++) {
			AnswerLayer.neurons.FindByIndex(i)->Output = *(answer->FindByIndex(i));
		}
	}
	void SetNeuronCounts(List<int>* NeuronCount) {
		if (HiddenLayerCount + 1!= NeuronCount->GetNodeCount()) {
			cout << "뉴런숫자 배열 개수와 레이어 수가 다릅니다. " << endl;
			for (int i = 0; i < NeuronCount->GetNodeCount(); i++) {
				cout << *(NeuronCount->FindByIndex(i)) << endl;
			}
			return;
		}

		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers.FindByIndex(i)->SetNeuronCount(*(NeuronCount->FindByIndex(i)));
		}
		OutputLayer.InitNeuron(*(NeuronCount->FindByIndex(HiddenLayerCount)));
		cout << "은닉층 뉴런 개수 설정 완료" << endl;
	}
	void SetBiasGroup(List<T3>* BiasGroup) {
		if (HiddenLayerCount + 1!= BiasGroup->GetNodeCount()) {
			cout << "bias 개수와 레이어 수가 다릅니다. " << BiasGroup->GetNodeCount() << "개" << endl;
			for (int i = 0; i < BiasGroup->GetNodeCount(); i++) {
				cout << *(BiasGroup->FindByIndex(i)) << endl;
			}
			return;
		}
		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers.FindByIndex(i)->SetBias(*(BiasGroup->FindByIndex(i)));
		}
		OutputLayer.SetBias(*(BiasGroup->FindByIndex(HiddenLayerCount)));
		cout << "bias 설정 완료" << endl;
	}
	void SetActivationFunc(List<T3(*)(T3 x)>* ActFuncMass) {
		if (HiddenLayerCount + 1 != ActFuncMass->GetNodeCount()) {
			cout << "활성화 함수 개수와 레이어 수가 다릅니다. " << endl;
			return;
		}
		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers.FindByIndex(i)->SetActiveFunc(*(ActFuncMass->FindByIndex(i)));
		}
		OutputLayer.SetActiveFunc(*(ActFuncMass->FindByIndex(HiddenLayerCount)));
		cout << "활성화 함수 설정 완료" << endl;
	}

	void InitWeighs() {
		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers.FindByIndex(i)->InitWeighsFromIn();
		}
		OutputLayer.InitWeighsFromIn();
		cout << "가중치 랜덤 설정 완료" << endl;
	}

	void FeedForward() {
		for (int i = 0; i < HiddenLayerCount; i++) {
			HiddenLayers.FindByIndex(i)->SetInputsFromIn();
			HiddenLayers.FindByIndex(i)->FeedForward();
			 
		}
		OutputLayer.SetInputsFromIn();
		OutputLayer.FeedForward();
		cout << "앞먹임 시행 완료" << endl;
	}
	void PrintAllLayer() {
		Layer<T3>* LayerExplorer = &InputLayer;
		for (int i = 0; i < HiddenLayerCount + 2; i++) {
			for (int k = 0; k < LayerExplorer->GetNeuronCount(); k++) {
				cout << LayerExplorer->neurons.FindByIndex(k)->Output << " ";
			}
			cout << endl;
			LayerExplorer = LayerExplorer->pNextLayer;
		}
	}
	void ConnectHiddenLayersAndIOLayers() {
		Layer<T3>* pLayerConnector;
		for (int i = 0; i < HiddenLayers.GetNodeCount(); i++) {
			pLayerConnector = &HiddenLayers[i];
			if (i == 0) {
				pLayerConnector->pPrevLayer = &InputLayer;
				pLayerConnector->pNextLayer = &HiddenLayers[i + 1];
			}
			else if (i == HiddenLayers.GetNodeCount() - 1) {
				pLayerConnector->pPrevLayer = &HiddenLayers[i - 1];
				pLayerConnector->pNextLayer = &OutputLayer;
			}
			else {
				pLayerConnector->pPrevLayer = &HiddenLayers[i - 1];
				pLayerConnector->pNextLayer = &HiddenLayers[i + 1];
			}

		}
	}
private:
	List<Layer<T3>> HiddenLayers;
	Layer<T3> InputLayer,  AnswerLayer, OutputLayer;
	List<int> HiddenLayerNeuronCounts;
	int HiddenLayerCount;
	T3 LearningConst;
};

