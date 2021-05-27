#pragma once
#include <memory.h>
#include <iostream>
#include <string>
template <typename T2>
struct Node {
	struct Node* pNext;
	T2 data;
};
template <typename T1>
class List {

	Node<T1>* pHead;
	int Nodecnt = 0;
public:
	List<T1>() {
		Init();
	}
	~List<T1>() {

	}
	void InsertFirst(T1 data);
	void Init();
	void InsertLast(T1 data);
	Node<T1>* Findfirst(T1 dataTarget);
	T1* FindByIndex(int index);
	void Remove(T1 dataTarget);
	void Insert(T1 prevData, T1 nextData, T1 data);
	void PrintAll();
	T1& operator[](int i) {
		return *(FindByIndex(i));
	}
	int GetNodeCount() {
		return Nodecnt;
	}
};
using namespace std;
template <typename T1>
void List<T1>::Init() {
	pHead = nullptr;
	Nodecnt = 0;
}
template <typename T1>
void List<T1>::InsertFirst(T1 data) {
	Node<T1>* temp = new Node<T1>;
	if (temp == nullptr) {
		cout << "힙메모리 오버플로우" << endl;
		return;
	}
	temp->data = data;
	temp->pNext = nullptr;

	Nodecnt++;

	if (pHead == nullptr) {
		pHead = temp;
	}
	else {
		temp->pNext = pHead;
		pHead = temp;
	}
}
template <typename T1>
void List<T1>::InsertLast(T1 data) {
	Node<T1>* temp = new Node<T1>;
	if (temp == nullptr) {
		cout << "힙메모리 오버플로우" << endl;
		return;
	}
	temp->data = data;
	temp->pNext = nullptr;

	Node<T1>* explorer = nullptr;
	if (pHead == nullptr) {

		pHead = temp;
	}
	else {
		explorer = pHead;
		for (int i = 0; i < Nodecnt; i++) {
			if (explorer->pNext == nullptr) {
				explorer->pNext = temp;
				break;
			}
			else {
				explorer = explorer->pNext;
			}
		}
	}



	Nodecnt++;
}
template <typename T1>
void List<T1>::Insert(T1 prevData, T1 nextData, T1 data) {
	Node<T1>* temp = new Node<T1>;
	if (temp == nullptr) {
		cout << "힙메모리 오버플로우" << endl;
		return;
	}
	temp->data = data;
	temp->pNext = nullptr;

	Node<T1>* explorer = pHead;
	if (explorer == nullptr) {
		return;
	}
	while (explorer->pNext != nullptr) {
		if (explorer->pNext->data == nextData && explorer->data == prevData) {
			temp->pNext = explorer->pNext;
			explorer->pNext = temp;
			Nodecnt++;
			break;

		}

		explorer = explorer->pNext;



	}


}
template <typename T1>
Node<T1>* List<T1>::Findfirst(T1 dataTarget) {
	Node<T1>* finder = pHead;
	for (int i = 0; i < Nodecnt; i++) {
		if (finder->data == dataTarget) {
			return finder;
		}
		else {
			finder = finder->pNext;
		}
	}
	return nullptr;
}
template <typename T1>
T1* List<T1>::FindByIndex(int index) {
	Node<T1>* finder = pHead;
	if (finder == nullptr) {
		cout << "리스트에 값이 존재하지 않습니다." << endl;
		return nullptr;
	}
	for (int i = 0; i < index; i++) {
		finder = finder->pNext;
		if (finder == nullptr) {
			return nullptr;
		}
	}
	return &(finder->data);
}
template <typename T1>
void List<T1>::Remove(T1 dataTarget) {
	if (dataTarget == pHead->data) {
		Node<T1>* RemoveTarget = pHead;
		pHead = pHead->pNext;
		delete RemoveTarget;
		Nodecnt--;
	}

	Node<T1>* finderPrev = pHead;

	while (finderPrev->pNext != nullptr) {
		if (finderPrev->pNext->data == dataTarget) {
			Node<T1>* RemoveTarget = finderPrev->pNext;
			finderPrev->pNext = finderPrev->pNext->pNext;
			delete RemoveTarget;
			Nodecnt--;
		}
		else {
			finderPrev = finderPrev->pNext;
		}
	}


}
template <typename T1>
void List<T1>::PrintAll() {
	Node<T1>* finder = pHead;

	for (int i = 0; i < Nodecnt; i++) {
		cout << "Target[" << i << "]" << " = " << finder->data << endl;
		finder = finder->pNext;
	}
}
