#pragma once
#include "NeuronSet.h"
#include <thread>
#include <vector>
template <typename T2>
class Layer {
public:
	Layer(){
		
	}
	~Layer() {
		delete[] neurons;
	}
	int GetNeuronCount() {
		return NeuronCount;
	}
	void InitNeuron(int neuronCount) {
		NeuronCount = neuronCount;
		for (int i = 0; i < neuronCount; ++i) neurons = new Neuron<T2>[neuronCount];
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
		for (int i = 0; i < NeuronCount; ++i) neurons[i].InitInputsFromIn(InputsFromIn);
		
	}
	void SetInputsFromIn() {
		for (int i = 0; i < pPrevLayer->NeuronCount; i++) {
			InputsFromIn[i] = pPrevLayer->neurons[i].Output;
			//cout << "이전 결과값 : " << pPrevLayer->neurons[i].Output << endl;
		}

	}
	inline void TerminateInputsFromIn(){ delete[] InputsFromIn; }

	inline void InitWeighsFromIn() {
		for (int i = 0; i < NeuronCount; ++i)
			neurons[i].InitWeighsFromIn(pPrevLayer->NeuronCount);
	}
	void SetWeighsFromOut() {
		T2*** temp = new T2 **[NeuronCount];

		for (int i = 0; i < NeuronCount; i++) {
			temp[i] = new T2*[pNextLayer->NeuronCount];
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
		T2* deltas = new T2[pNextLayer->NeuronCount];
		for (int i = 0; i < pNextLayer->NeuronCount; i++) {
			deltas[i] = pNextLayer->neurons[i].OutputDelta;
		}
		for (int i = 0; i < NeuronCount; ++i) neurons[i].SetDeltasFromOut(deltas, pNextLayer->NeuronCount);
		delete[] deltas;
	}
  void FeedForward_block(int start, int end, int thread_num) { //멀티스레드 테스트중
			for (int i = start; i < end; ++i)neurons[i].FeedForward();
			//std::cout << thread_num << "번째 스레드 작동중" << std::endl;
	}

	void FeedForward() {

		const int super_count = 8;
		std::thread jobs[super_count];

		int block = NeuronCount / super_count;

		for (int i = 0; i < super_count; ++i) {
			jobs[i] = std::thread(&Layer::FeedForward_block, this, i * block, block * (i + 1), i);
		}
		for (int i = 0; i < super_count; ++i) {
			jobs[i].join();
		}
		for (int i = 0; i < NeuronCount % super_count - 1; i++) {
			FeedForward_block(i, i + 1, -1);
		}
	}

	inline void BackPropWeighsFromOut() { for (int i = 0; i < NeuronCount; ++i) neurons[i].BackPropWeighsFromIn();}

	void BackPropogation() { //가중치 백프로포게이션(
		if (IsOutputLayer) {
			for (int i = 0; i < NeuronCount; ++i)neurons[i].BackPropogation(pNextLayer->neurons[i].Output - neurons[i].Output);
			BackPropWeighsFromOut();
		}
		else {
			SetWeighsFromOut();
			SetDeltasFromOut();
			for (int i = 0; i < NeuronCount; ++i) neurons[i].BackPropogation();
			BackPropWeighsFromOut();
		}
	
	}
	Layer<T2>* pPrevLayer = nullptr, * pNextLayer = nullptr;
	Neuron<T2>* neurons;
protected:
	bool IsOutputLayer = false;
	T2* InputsFromIn = nullptr;
	T2(*pActFunc)(T2 x) = nullptr;
	T2(*pActFuncGradient)(T2 x) = nullptr;
	int NeuronCount = 0;
	T2 Bias = 0;
	T2 learningConst = 0;
	void (Layer<T2>::*x)(int a, int b, int c);
};
