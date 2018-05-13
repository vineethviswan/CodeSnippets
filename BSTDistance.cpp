
#include <iostream>
#include <vector>
#include <exception>

using namespace std;

struct Node {
	int mData;
	Node *left;
	Node *right;
};

class BST {

public:
	BST();
	int bstDistance(int *numbers, int count, int node1, int node2);
	void addNode(int elt);
	void addNode(Node *, Node *);
	Node *getNode();
	int findDistanceWithPath(int, vector<int> *);
	int findLCA(int, int);

private:
	Node *bst;
	vector<int> node1Path, node2Path;
};

BST::BST() {
	bst = nullptr;
}

int BST::findLCA(int node1, int node2) {
	for (int i = 0; i != node1Path.size() && i != node2Path.size(); i++) {
		if (node1Path[i] != node2Path[i]) {
			return (node1Path[i - 1]);
		}
	}
	return node1Path[0];
}

int BST::findDistanceWithPath(int elt, vector<int> *path = nullptr) {
	
	Node *itr = bst;
	int dist = 0;
	
	if (itr == nullptr)
		return dist;

	if (elt == itr->mData)
		return 1;

	while (itr) {
		if (path != nullptr)
			path->push_back(itr->mData);

		if (itr->mData == elt)
			return dist;
		else {
			if (elt < itr->mData)
				itr = itr->left;
			else
				itr = itr->right;
			dist++;
		}
	}

	return 0;
}

Node* BST::getNode() {

	Node *temp = new Node;
	if (temp == nullptr)
		throw exception("Memory Allocation Error..!");

	temp->mData = 0;
	temp->left = nullptr;
	temp->right = nullptr;

	return temp;
}

void BST::addNode(int elt) {

	Node *tempNode = getNode();
	tempNode->mData = elt;

	if (bst == nullptr)
		bst = tempNode;
	else
		addNode(bst, tempNode);
}

void BST::addNode(Node *itr, Node *tmp) {

	if (itr->mData >= tmp->mData) {
		if (itr->left == nullptr) {
			itr->left = tmp;

		}
		else
			addNode(itr->left, tmp);
	}
	else if (itr->mData < tmp->mData) {
		if (itr->right == nullptr) {
			itr->right = tmp;
		}
		else
			addNode(itr->right, tmp);
	}
		
}

int BST::bstDistance(int *numbers, int count, int node1, int node2) {

	int node1Dist = 0, node2Dist = 0, lca = 0;
	
	for (int i = 0; i < count; i++)
		addNode(numbers[i]);

	node1Dist = findDistanceWithPath(node1, &node1Path);
	node2Dist = findDistanceWithPath(node2, &node2Path);
	if (!node1Dist || !node2Dist)
		return -1;

	lca = findLCA(node1, node2);
	return (node1Dist + node2Dist - (2 * findDistanceWithPath(lca)));

}

int main() {

	BST bst;
	int nodes[] = { 1, 2, 4, 5, 6, 7 };
	cout << bst.bstDistance(nodes, 6, 2, 6) << endl;
	return 0;
}