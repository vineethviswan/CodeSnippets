

#include<iostream>
#include<exception>
#include<vector>

using namespace std;

struct Node {
	int mData;
	struct Node *left;
	struct Node *right;
	struct Node *parent;
	int level;
} ;

class BinaryTree {
public:
	BinaryTree();
	~BinaryTree();
	Node *getNode();
	void addNode(int);
	void inOrderTraverse();
	void preOrderTraverse();
	void postOrderTraverse();
	void deleteNode(int);
	Node* findKey(int);
	int getMaxLevel();
	void sumByLevel();
	int getTreeHeight();
	int depthofNode(int elt);

private:
	Node *root;
	int highestLevel;
	void addNode(Node*, Node *);
	void inOrder(Node*);
	void preOrder(Node*);
	void postOrder(Node*);
	void deleteNode(Node *, int);
	int minValue(Node*);
	void sumHelper(vector<int> &sum, Node *itr);
	int heightofTree(Node *);
	void deleteTree(Node *);
};

int BinaryTree::getTreeHeight() {
	return heightofTree(root);
}

int BinaryTree::depthofNode(int elt) {
	Node *nodeRef = findKey(elt);
	if (nodeRef != nullptr)
		return nodeRef->level;
	else
		return -1;
}

int BinaryTree::heightofTree(Node *itr) {

	if (itr == nullptr)
		return -1;
	else {
		int lhsHeight = heightofTree(itr->left);
		int rhsHeight = heightofTree(itr->right);
		if (lhsHeight > rhsHeight)
			return lhsHeight + 1;
		else
			return rhsHeight + 1;
	}
}

int BinaryTree::getMaxLevel() {
	return highestLevel;
}

void BinaryTree::inOrder(Node *itr) {
	
	if (itr != nullptr) {
		inOrder(itr->left);
		cout << itr->mData << " " ;
		inOrder(itr->right);
	}

	return;
}

void BinaryTree::sumHelper(vector<int> &sum, Node *itr) {
	
	if (itr != nullptr) {
		sumHelper(sum, itr->left);
		sum[itr->level] += itr->mData;
		sumHelper(sum, itr->right);
	}
}

void BinaryTree::sumByLevel() {

	vector<int> levelSum(highestLevel + 1, 0);

	if (root == nullptr) {
		cout << "Empty Tree..!!!" << endl;
		return;
	}

	sumHelper(levelSum, root);

	cout << "Sum by Level" << endl;
	for (int i = 0; i < highestLevel + 1; i++)
		cout << i << " - " << levelSum[i] << endl;
}

Node* BinaryTree::findKey(int key) {
	
	Node *itr = root;
	if (root == nullptr)
		cout << "Empty Tree..!!!" << endl;

	while (itr) {
		if (itr->mData == key)
			return itr;
		else if (key < itr->mData)
			itr = itr->left;
		else
			itr = itr->right;
	}

	return nullptr;
}

void BinaryTree::inOrderTraverse() {
	inOrder(root);
}

void BinaryTree::preOrder(Node *itr) {

	if (itr != nullptr) {
		cout << itr->mData << " ";
		preOrder(itr->left);
		preOrder(itr->right);
	}

	return;
}

void BinaryTree::preOrderTraverse() {
	preOrder(root);
}

void BinaryTree::postOrder(Node *itr) {

	if (itr != nullptr) {
		postOrder(itr->left);
		postOrder(itr->right);
		cout << itr->mData << " ";
	}
	return;
}

void BinaryTree::postOrderTraverse() {
	postOrder(root);
}

BinaryTree::BinaryTree() {
	root = nullptr;
	highestLevel = 0;
}

void BinaryTree::deleteTree(Node *itr) {

	if (itr != nullptr) {
		postOrder(itr->left);
		postOrder(itr->right);
		deleteNode(itr->mData);
	}
}

BinaryTree::~BinaryTree()
{
	if (root)
		deleteTree(root);
}

void BinaryTree::deleteNode(int elt) {

	if (root == nullptr)
		throw exception("Tree Empty..!!");
	else
		deleteNode(root, elt);
}

void BinaryTree::deleteNode(Node *itr, int elt) {

	Node *toDelete = nullptr;

	if (elt < itr->mData) {
		if (itr->left == nullptr) {
			cout << "Element Not Found..!!" << endl;
			return;
		}
		else
			deleteNode(itr->left, elt);
	} 
	else if (elt > itr->mData) {
		if (itr->right == nullptr) {
			cout << "Element Not Found..!!" << endl;
			return;
		}
		else
			deleteNode(itr->right, elt);
	}
	else if (itr->mData == elt) {
		if (itr->left == nullptr && itr->right == nullptr) {
			
			toDelete = itr;
			if (itr == (itr->parent)->left)
				(itr->parent)->left = nullptr;
			else
				(itr->parent)->right = nullptr;
		}
		else if (itr->left == nullptr && itr->right != nullptr) {
			
			toDelete = itr;
			if (itr == (itr->parent)->left)
				(itr->parent)->left = itr->right;
			else
				(itr->parent)->right = itr->right;
		}
		else if (itr->left != nullptr && itr->right == nullptr) {
			
			toDelete = itr;
			if (itr == (itr->parent)->left)
				(itr->parent)->left = itr->left;
			else
				(itr->parent)->right = itr->left;
		}
		else if (itr->left != nullptr && itr->right != nullptr) {
			itr->mData = minValue(itr->right);
			deleteNode(itr->right, itr->mData);
		}
	}
}

int BinaryTree::minValue(Node *itr) {
	if (itr->left == nullptr)
		return itr->mData;
	else
		return minValue(itr->left);
}

void BinaryTree::addNode(int elt) {

	Node *tempNode = getNode();
	tempNode->mData = elt;

	if (root == nullptr)
		root = tempNode;
	else if (root->mData == elt)
		cout << "Element already exists in tree...!!" << endl;
	else
		addNode(root, tempNode);

	//update the level
	if (tempNode->level > highestLevel)
		highestLevel = tempNode->level;
}

void BinaryTree::addNode(Node *itr, Node *tempNode) {

	if (tempNode->mData < itr->mData) {
		if (itr->left == nullptr) {
			tempNode->level++;
			itr->left = tempNode;
			tempNode->parent = itr;
		}
		else {
			tempNode->level++;
			addNode(itr->left, tempNode);
		}
	}
	else if (tempNode->mData > itr->mData) {
		if (itr->right == nullptr) {
			itr->right = tempNode;
			tempNode->level++;
			tempNode->parent = itr;
		}
		else {
			tempNode->level++;
			addNode(itr->right, tempNode);
		}
	}
}

Node* BinaryTree::getNode() {
	
	Node *temp = new Node;
	if (!temp)
		throw exception("Memory Allocation Error..!!!");

	temp->mData = 0;
	temp->left = nullptr;
	temp->right = nullptr;
	temp->parent = nullptr;
	temp->level = 0;

	return temp;
}

int main() {

	BinaryTree bst;

	bst.addNode(8);
	bst.addNode(4);
	bst.addNode(1);
	bst.addNode(5);	
	bst.addNode(12);
	bst.addNode(11);
	bst.addNode(14);
	bst.addNode(13);
	bst.addNode(15);

	bst.inOrderTraverse();
	cout << endl << "Max Level - " << bst.getMaxLevel() << endl;
	bst.sumByLevel();

	cout << "Height of Tree - " << bst.getTreeHeight() << endl;
	cout << "Depth of Node 15 - " << bst.depthofNode(15) << endl;

	/*bst.addNode(5);
	bst.addNode(2);
	bst.addNode(1);
	bst.addNode(3);
	bst.addNode(10);
	bst.addNode(7);
	bst.addNode(15);

	cout << endl << "In Order Traversal " << endl;
	bst.inOrderTraverse();

	cout << endl << "Pre Order Traversal " << endl;
	bst.preOrderTraverse();

	cout << endl << "Post Order Traversal " << endl;
	bst.postOrderTraverse();

	//cout << endl << "Deleting 1" << endl;
	//bst.deleteNode(1);
	//bst.inOrderTraverse();

	//cout << endl << "Deleting 5" << endl;
	//bst.deleteNode(5);
	//bst.inOrderTraverse();

	cout << endl << "Searching for 20" << endl;
	cout << (bst.findKey(20) ? " Found " : " Not Found") << endl;

	cout << endl << "Searching for 10" << endl;
	cout << (bst.findKey(10) ? " Found " : " Not Found") << endl;
	*/

	return 0;
}