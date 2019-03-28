#pragma once
template<class Type>
class PriorityQueue {
	Type *elements;
	int max_size;
	int last_index = -1;
private:
	void max_heapify(int index);
public:
	PriorityQueue();
	PriorityQueue(int size);
	Type peek();
	Type pop();
	void push(Type element);
};

template<class Type>
void PriorityQueue<Type>::max_heapify(int index) {
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	if(left > last_index) {
		return;
	}
}
