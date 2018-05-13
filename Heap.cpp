
#include <iostream>
#include <exception>
#include <iomanip>

using namespace std;

class MinHeap {
public:
	MinHeap(const int c) :capacity(c) {
		size = 0;
		theArray = new int[capacity];
		if (theArray == nullptr)
			throw exception("Memory Allocation Error..!");
	}
	~MinHeap();

	int peek();
	void add(int elt);
	void poll();
	void printHeap();
	int getHeapCapacity() { return capacity; }

private:
	int *theArray;
	const int capacity;
	int size;

	int getParentIndex(int childIndex) { return (childIndex - 1) / 2; }
	int getLeftChildIndex(int parentIndex) { return (parentIndex * 2) + 1; }
	int getRightChildIndex(int parentIndex) { return (parentIndex * 2) + 2; }

	int getParent(int index) { return theArray[getParentIndex(index)]; }
	int getLeftChild(int index) { return theArray[getLeftChildIndex(index)]; }
	int getRightChild(int index) { return theArray[getRightChildIndex(index)]; }

	int hasParent(int index) { return getParentIndex(index) >= 0; }
	int hasLeftChild(int index) { return getLeftChildIndex(index) < size; }
	int hasRightChild(int index) { return getRightChildIndex(index) < size; }

	void swap(int indxOne, int indxTwo);
	void makeItHeapUp();
	void makeItHeapDown();

	void extendHeap();
};

void MinHeap::extendHeap() {

	int *tempArray;
	if (size == capacity) {
		tempArray = new int[capacity * 2];
		if (tempArray == nullptr)
			throw exception("Memory Allocation Error..!!");

		for (int i = 0; i < size; i++)
			tempArray[i] = theArray[i];

		if (theArray)
			delete[] theArray;

		theArray = tempArray;
	}
}

void MinHeap::printHeap() {

	int i;
	for (i = 0; i < size; i++)
		cout << setw(5) << i ;
	cout << endl;
	for (i = 0; i < size; i++)
		cout << setw(5) << theArray[i] ;

	cout << endl;
}

void MinHeap::makeItHeapUp() {

	int index = size - 1;
	while (hasParent(index) && getParent(index) > theArray[index]) {
		swap(getParentIndex(index), index);
		index = getParentIndex(index);
	}

}

void MinHeap::makeItHeapDown() {
	
	int index = 0;
	while (hasLeftChild(index)) {
		int smallChildIndex = getLeftChildIndex(index);
		
		if (hasRightChild(index) && getRightChild(index) < getLeftChild(index))
			smallChildIndex = getRightChildIndex(index);
		
		if (theArray[index] < theArray[smallChildIndex])
			break;
		else
			swap(index, smallChildIndex);

		index = smallChildIndex;
	}
}

int MinHeap::peek() {

	if (size == 0)
		throw exception("Heap Empty..!!");
	 return theArray[0]; 
}

void MinHeap::add(int elt) {

	if (size == capacity - 1)
		extendHeap();

	theArray[size] = elt;
	size++;
	makeItHeapUp();

}

void MinHeap::poll() {

	int item;
	if (size == 0)
		throw exception("Heap Empty..!!");
	
	item = theArray[0];
	theArray[0] = theArray[size - 1];
	size--;
	makeItHeapDown();
}

void MinHeap::swap(int indxOne, int indxTwo) {

	int temp = theArray[indxOne];
	theArray[indxOne] = theArray[indxTwo];
	theArray[indxTwo] = temp;
}

MinHeap::~MinHeap() {
	if (theArray)
		delete[] theArray;
}

int main() {


	MinHeap heap(10);

	heap.add(9);
	heap.add(7);
	heap.add(15);
	heap.add(20);
	heap.add(4);
	heap.add(3);
	heap.add(8);
	heap.add(5);
	heap.add(10);

	heap.printHeap();

	heap.poll();
	cout << endl;
	heap.printHeap();

	heap.poll();
	cout << endl;
	heap.printHeap();

	heap.poll();
	cout << endl;
	heap.printHeap();

	heap.poll();
	cout << endl;
	heap.printHeap();

	return 0;
}
