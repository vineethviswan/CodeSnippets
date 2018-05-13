
#include <iostream>
#include <array>
#include <exception>
#include <random>
#include <list>

using namespace std;

class HashMap {
public:
	HashMap(const int size) :arraySize(size) {
		theArray = new int[arraySize];
		if (!theArray)
			throw exception("Memory Allocation Error..!!");

		for (int i = 0; i < arraySize; i++)
			theArray[i] = -1;

		map = new list<int>[arraySize];
		if (!map)
			throw exception("Memory Allocation Error..!!");
	}
	~HashMap();
	void hashFunction1(int *eltsToAdd, int size);
	void doubleHash(int *eltsToAdd, int size);
	void printMap();
	int findKey(int);
	int findKeyDoubleHash(int);
	int findKeyChaining(int);
	void separateChaining(int *eltsToAdd, int size);

private:
	const int arraySize;
	int *theArray;
	list<int> *map;

};

int HashMap::findKeyChaining(int key) {

	int arrayIndex = key % arraySize;
	for (auto itr = map[arrayIndex].begin(); itr != map[arrayIndex].end(); itr++) {
		if (*itr == key)
			return 1;
	}
	
	return 0;
}

void HashMap::separateChaining(int *eltsToAdd, int size) {

	for (int i = 0; i < size; i++) {
		int arrayIndex = eltsToAdd[i] % arraySize;
		map[arrayIndex].push_back(eltsToAdd[i]);
	}

	/*for (int i = 0; i < arraySize; i++) {
		cout << i << "\t";
		for (auto itr = map[i].begin(); itr != map[i].end(); itr++)
			cout << *itr << " ";
		cout << endl;
	}*/
}

HashMap::~HashMap() {
	if (theArray)
		delete[] theArray;
}

void HashMap::printMap() {

	cout << "Index	-  Value " << endl;
	for (int i = 0; i < arraySize; i++) {
		cout << i << "	-  ";
		if (theArray[i] == -1)
			cout << " " << endl;
		else
			cout << theArray[i] << endl;
	}
}

int HashMap::findKey(int eltToFind) {

	int arrayIndex = eltToFind % arraySize;

	while (theArray[arrayIndex] != -1) {
		if (theArray[arrayIndex] == eltToFind)
			return arrayIndex;
		++arrayIndex;
		if (arrayIndex == arraySize)
			arrayIndex = arrayIndex % arraySize;
	}
	return -1;
}

int HashMap::findKeyDoubleHash(int eltToFind) {

	int arrayIndex = eltToFind % arraySize;
	int stepDist = 7 - (eltToFind % 7);

	while (theArray[arrayIndex] != -1) {
		if (theArray[arrayIndex] == eltToFind)
			return arrayIndex;
		arrayIndex += stepDist;
		if (arrayIndex == arraySize)
			arrayIndex = arrayIndex % arraySize;
	}
	return -1;
}

void HashMap::doubleHash(int *eltsToAdd, int size) {

	for (int i = 0; i < size; i++) {
		int arrayIndex = eltsToAdd[i] % arraySize;
		int stepDist = 7 - (eltsToAdd[i] % 7);
		
		while (theArray[arrayIndex] != -1) {
			arrayIndex += stepDist;
			if (arrayIndex == arraySize)
				arrayIndex = arrayIndex % arraySize;
		}

		theArray[arrayIndex] = eltsToAdd[i];
	}
}

void HashMap::hashFunction1(int *eltsToAdd, int size) {

	for (int i = 0; i < size; i++) {
		int arrayIndex = eltsToAdd[i] % arraySize;
		
		while (theArray[arrayIndex] != -1) {
			++arrayIndex;
			if (arrayIndex == arraySize)
				arrayIndex = arrayIndex % arraySize;
		}

		theArray[arrayIndex] = eltsToAdd[i];
	}
}

int main() {

	HashMap map(30);
	int arr[30];
	for (int i = 0; i < 30; i++) {
		arr[i] = rand() % 171;
	}

	map.separateChaining(arr, 30);

	if (map.findKeyChaining(135))
		cout << " Element Found" << endl;
	else
		cout << " Element Not Found" << endl;

	//map.doubleHash(arr, 15);
	//map.printMap();

	//int ret = map.findKeyDoubleHash(166);
	//if (ret != -1)
	//	cout << "Element found at index " << ret << endl;
	//else
	//	cout << "Element Not Found" << endl;

	return 0;
}