
#include <iostream>
#include <exception>

using namespace std;

class theArray {
public:
	theArray(const int n) : size(n) {
		mData = new int[size];

		if (!mData)
			throw exception("Memory Allocation Error ..!!");


		if (mData) {
			for (int i = 0; i < size; i++) {
				mData[i] = rand() % 127;
			}

		}

	}
	void LinearSearch(int Item);
	void printArray(int index);
	void bubbleSort();
	void swap(int &, int &);
	void binarySearch(int Item);
	void selectionSort();
	void insertionSort();
	void shellSort();

	void qSort(int, int);
	void quickSort();
	int partition(int, int, int);

	void merge(int, int, int);
	void mergeSort(int, int);

private:
	int *mData;
	const int size;
};

void theArray::swap(int &first, int &second) {
	int temp;

	temp = first;
	first = second;
	second = temp;

}

//Bubble sort
void theArray::bubbleSort() {

	for (int i = size - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (mData[j] > mData[j + 1])
				swap(mData[j], mData[j + 1]);
		}
	}


}
void theArray::printArray(int index = -1) {

	if (index == -1) {
		for (int i = 0; i < size; i++)
			cout << mData[i] << " ";
	}
	else
		cout << "Element At " << index + 1 << " - " << mData[index] << endl;

	cout << endl;
}

//Binary Search
void theArray::binarySearch(int Item) {

	int lowIndex = 0, highIndex = size - 1, midIndex;
	midIndex = (lowIndex + highIndex) / 2;
	bool itemFound = false;
	
	while (lowIndex <= highIndex) {
		
		if (Item == mData[midIndex]) {
			cout << "Item " << Item << "Found at " << midIndex + 1 << endl;
			itemFound = true;
			break;
		}	
		else if (Item < mData[midIndex])
			highIndex = midIndex - 1;
		else if (Item > mData[midIndex])
			lowIndex = midIndex + 1;
		 
		midIndex = (lowIndex + highIndex) / 2;
	}

	if (!itemFound)
		cout << "Item Not Found in Array " << endl;

}

//Linear Search
void theArray::LinearSearch(int Item) {

	int itemFoundIndex;
	bool found = false;

	for (int i = 0; i < size; i++) {
		if (mData[i] == Item) {
			found = true;
			itemFoundIndex = i;
			break;
		}
	}

	if (found)
		cout << "Item Found at - " << itemFoundIndex + 1 << endl;
	else
		cout << "Item " << Item << " Not found in Array " << endl;
}

//Selection Sort
void theArray::selectionSort() {

	int minIndex; 
	for (int i = 0; i < size; i++)
	{
		minIndex = i;
		for (int j = i + 1; j < size; j++)
		{
			if (mData[j] > mData[minIndex])
				minIndex = j;
		}

		if (i != minIndex)
			swap(mData[i], mData[minIndex]);
	}
}

//Insertion Sort
void theArray::insertionSort() {

	int toInsert;

	for (int i = 1; i < size; i++) {
		int j = i;
		toInsert = mData[j];
		while (j > 0 && mData[j - 1] > toInsert) {
			mData[j] = mData[j - 1];
			j--;
		}
		mData[j] = toInsert;
	}
}

//Shell Sort
void theArray::shellSort() {

	int temp, inner, outer, incr;

	for (incr = size / 3; incr > 0; incr /= 3) {
		for (outer = incr; outer < size; outer++) {
			temp = mData[outer];
			inner = outer;
			while (inner >= incr && temp < mData[inner - incr]) {
				mData[inner] = mData[inner - incr];
				inner -= incr;
			}
			mData[inner] = temp;
		}
	}
}

//Quick Sort
void theArray::qSort(int left, int right) {

	int pivot;

	if (right - left <= 0)
		return;
	else {
			pivot = mData[right];
			pivot = partition(left, right, pivot);
			qSort(left, pivot - 1);
			qSort(pivot + 1, right);
		}
}

int theArray::partition(int left, int right, int pivot) {

	int leftptr = left - 1;
	int rightptr = right;

	while (true) {

		while (leftptr < size-1 && mData[++leftptr] < pivot)
			;
		while (rightptr > 0 && mData[--rightptr] > pivot)
			;
		if (leftptr >= rightptr)
			break;
		else
			swap(mData[leftptr], mData[rightptr]);
	}

	swap(mData[right], mData[leftptr]);
	return leftptr;

}

void theArray::quickSort() {

	qSort(0, size - 1);
}

void theArray::merge(int low, int high, int mid) {

	int i = low, j = mid + 1, k = low;
	
	int *temp = new int[size];
	if (!temp)
		throw exception("Memory allocation error..!!");

	while (i <= mid && j < high) {
		if (mData[i] < mData[j])
			temp[k++] = mData[i++];
		else
			temp[k++] = mData[j++];
	}

	while (i <= mid) {
		temp[k++] = mData[i++];
	}

	while (j < high) {
		temp[k++] = mData[j++];
	}

	for (i = low; i < k; i++)
		mData[i] = temp[i];

	if (temp)
		delete[]temp;
}

void theArray::mergeSort(int low, int high) {

	if (low < high) {
		int mid = (low + high) / 2;
		mergeSort(low, mid);
		mergeSort(mid + 1, high);
		merge(low, high, mid);
	}
}

int main() {

	try {

		theArray obj(15);
		obj.printArray();
		//obj.LinearSearch(10);
		//obj.selectionSort();
		//obj.bubbleSort();
		//obj.insertionSort();
		//obj.shellSort();
	
		obj.quickSort();
		obj.printArray();

		//obj.binarySearch(58);
	}
	catch (exception  e) {
		cout << e.what() << endl;
	}

	return 0;

}