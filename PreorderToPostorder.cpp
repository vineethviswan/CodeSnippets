
#include <iostream>
#include <vector>

using namespace std;

bool checkIfSorted(vector<int> &bst, int beg, int end) {

	for (int i = beg; i <= end; i++) {
		int j = i + 1;
		
		while (j <= end && i <= end && bst[j] <= bst[i])
			j++;

		int k = j;
		while (k <= end) {
			if (bst[k] >= bst[i])
				k++;
			else
				return false;
		}
	}
	return true;
}

void toPostOrder(vector<int> &bst, int beg, int end) {

	int i = beg + 1, root = bst[beg];

	if (beg == end) {
		cout << bst[beg] << " ";
		return;
	}

	while (bst[i] <= root && i <= end) {
		i++;
		if (i > end)
			break;
	}
	
	if(i != beg + 1) 
		toPostOrder(bst, beg + 1, i - 1);
	
	if(i <= end)
		toPostOrder(bst, i, end);

	cout << root << " ";
}

int main() {

	int tests, size; // , elts, i;

	vector<int> theArray = { 40, 30, 25, 50, 45 };

	//cin >> tests;
	tests = 1;
	while (tests--) {
		//cin >> size;
		size = 5;

		/*i = 0;
		while (i < size) {
			cin >> elts;
			theArray.push_back(elts);
			i++;
		}*/
		
		if(checkIfSorted(theArray, 0, size - 1))
			toPostOrder(theArray, 0, size - 1);
		else
			cout << "NO";

		//cleanup
		cout << endl;
		theArray.clear();
	}

	return 0;
}

