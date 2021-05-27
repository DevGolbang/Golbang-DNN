#pragma once
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <cassert>
#include <iostream>


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

	void SetDeltasFromOut(T1 deltas[], int &_count) {
		DeltasFromOut = new T1[_count];
		for(int i = 0; i < _count; ++i) DeltasFromOut[i] = deltas[i];
	}
	inline void TerminateDeltasFromOut() {delete[] DeltasFromOut;}

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
		WeighSum = 0; //앞먹임 가중합
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