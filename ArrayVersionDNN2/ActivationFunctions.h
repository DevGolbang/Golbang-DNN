#pragma once
#include <cmath>
inline float Sigmoid(float x) {
	return 1.0f / (1.0f + exp(-x));
}
inline float SigmoidPrime(float x) {
	return Sigmoid(x) * (1.0f - Sigmoid(x));
}
inline float LinearFunc(float x) {
	return x;
}
inline float LinearFuncGradient(float x) {
	return 1.0f;
}