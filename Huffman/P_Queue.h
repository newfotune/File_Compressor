#pragma once
#include <vector>
#include <iostream>
#include <assert.h>

template <typename T> class Priority_Queue {
public:
	Priority_Queue() {
		arr.resize(1);
	}
	void push(const T element);
	T pop();
	size_t size();
	bool isEmpty();

	//delete this function;
	void print();

private:
	std::vector<T> arr;
	unsigned int current_spot = 1;
	int getParentIndex(int);
	int getRightIndex(int);
	int getLeftIndex(int);

};

template <typename T>
int Priority_Queue<T>::getParentIndex(int i) { return std::floor(i / 2); }
template <typename T>
int Priority_Queue<T>::getRightIndex(int i) { return (i * 2) + 1; }
template <typename T>
int Priority_Queue<T>::getLeftIndex(int i) { return i * 2; }

template <typename T>
bool Priority_Queue<T>::isEmpty() {
	return current_spot == 1;
}

template <typename T>
void Priority_Queue<T>::print() {
	for (int i = 1; i < current_spot; i++) {
		std::cout << arr[i].data << "->" << arr[i].total << " ";
	}	
	std::cout << std::endl;
}

template <typename T>
void Priority_Queue<T>::push(const T element) {
	T copy = element;
	arr[0] = copy; //store the new element at the sentinel spot

	auto hole = current_spot;

	if (current_spot == arr.size())
		arr.resize(current_spot * 2); //resize if we are running outta space

	for (; arr[getParentIndex(hole)] > element; hole /= 2) //while our new element is smaller than its parent
		arr[hole] = std::move(arr[getParentIndex(hole)]);      ///move the bigger element down

	arr[hole] = std::move(arr[0]); //insert the element at the right spot.
	current_spot++; //the current spot index increases
	//arr[0] = NULL;
}

/*
	Return the smallest element. If the queue is empty, it return null.
*/
template <typename T>
T Priority_Queue<T>::pop() {
	assert(!isEmpty()); //make sure that queue is not empty.

	int hole = 1;
	T element = arr[hole];
	T last_element = std::move(arr[current_spot-1]);
	
	while (getLeftIndex(hole) <= size() && getRightIndex(hole) <= size()) {
	//if the left element is less than or equal to the right element, move it up to the hole,
		if ((arr[getLeftIndex(hole)] <= arr[getRightIndex(hole)])) {
			arr[hole] = std::move(arr[getLeftIndex(hole)]);
			hole = getLeftIndex(hole);
		}
		else { // else move the right index;
			arr[hole] = std::move(arr[getRightIndex(hole)]);
			hole = getRightIndex(hole);
		}
	}
	
	current_spot--;
	arr[hole] = std::move(last_element);
	//arr[current_spot] = NULL;
	return element;
}

template <typename T>
size_t Priority_Queue<T>::size() {
	return current_spot-1;
}