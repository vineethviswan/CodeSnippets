
#include <iostream>
#include <exception>

using namespace std;

struct Node {
	int mData;
	struct Node *next;
	struct Node *prev;
};

class LinkedList {

public:
	LinkedList();
	~LinkedList();

	struct Node *getNewNode();
	void showList();
	void insertAt(int, int);
	void insertAfter(int, int);
	void deleteAt(int);
	void deleteElt(int);

private:
	struct Node *head;
	int size;
};

void LinkedList::deleteElt(int elt) {
	struct Node *itr = head, *tmp = nullptr;
	bool found = false;

	if (head == nullptr)
		cout << "Empty List...!!" << endl;

	while (itr) {
		if (itr->mData == elt ) {
			tmp = itr;
			if (itr == head) {
				head = itr->next;
				head->prev = nullptr;
				
			}
			else if (itr->next == nullptr)
			{
				(itr->prev)->next = nullptr;
			}
			else {
				(itr->prev)->next = itr->next;
				(itr->next)->prev = itr->prev;
			}
			
			found = true;
			size--;
			tmp->prev = nullptr;
			tmp->next = nullptr;
			break;
		}

		itr = itr->next;
	}

	if (itr == nullptr && !found)
		cout << "Element Not in List...!!" << endl;

	if (tmp)
		delete tmp;
}

void LinkedList::deleteAt(int pos) {
	struct Node *itr = head, *tmp;
	int i = 1;
	
	if (pos == 0 || pos > size) {
		cout << "Enter a valid Position..!!" << endl;
		return;
	}

	if (!size && !head) {
		cout << "Empty List..!!!" << endl;
		return;
	}

	if (pos == 1) {
		tmp = head;
		head = head->next;
		head->prev = nullptr;
		size--;
	}
	else {
		while (itr) {
			if(itr->next != nullptr)
				itr = itr->next;
			if (++i == pos)
				break;
		}
		if (pos == size) {
			tmp = itr;
			(itr->prev)->next = nullptr;
			size--;
			tmp->prev = nullptr;
		}
		else {
			tmp = itr;
			(itr->prev)->next = itr->next;
			(itr->next)->prev = itr->prev;
			size--;
			tmp->next = nullptr;
			tmp->prev = nullptr;
		}	
	}
	if (tmp)
		delete tmp;
}

struct Node* LinkedList::getNewNode() {
	struct Node *tmp = new struct Node;
	if (!tmp)
		throw exception("Memory Allocation Error..!!");

	tmp->mData = 0;
	tmp->next = nullptr;
	tmp->prev = nullptr;

	return tmp;
}

void LinkedList::insertAfter(int eltAfter, int elt) {
	struct Node *itr = head, *newNode;
	bool found = false;
	
	while (itr) {
		if (itr->mData == eltAfter) {
			if (itr->next != nullptr) {
				newNode = getNewNode();
				newNode->mData = elt;
				newNode->next = itr->next;
				newNode->prev = itr;
				(itr->next)->prev = newNode;
				itr->next = newNode;
				found = true;
				size++;
				break;
			}
			else {
				newNode = getNewNode();
				newNode->mData = elt;
				itr->next = newNode;
				newNode->prev = itr;
				found = true;
				size++;
				break;
			}
			
		}
		itr = itr->next;
	}

	if(!itr && !found)
		cout << "Element Not Found...!!!" << endl;

}

void LinkedList::insertAt(int pos, int elt) {
	
	struct Node *itr = head, *newNode;
	int i = 1;

	if (size == 0)
		pos = 1;

	if (pos == 0 || pos > size + 1) {
		cout << "Enter a valid Position..!!" << endl;
		return;
	}
	
	if (pos == 1) {
		newNode = getNewNode();
		newNode->mData = elt;
		newNode->next = head;
		head = newNode;
		size++;
	}
	else {
		while (itr) {
			if(itr->next != nullptr)
				itr = itr->next;		
			if (++i == pos)
				break;
		}
		if (pos == size + 1) {
			newNode = getNewNode();
			newNode->mData = elt;
			newNode->prev = itr;
			itr->next = newNode;
			size++;
		}
		else {
			newNode = getNewNode();
			newNode->mData = elt;
			newNode->next = itr;
			newNode->prev = itr->prev;
			(itr->prev)->next = newNode;
			itr->prev = newNode;

			size++;
		}
	}
	
}

LinkedList::LinkedList() {
	head = nullptr;
	size = 0;
}

LinkedList::~LinkedList() {
	if (head)
		delete head;
}

void LinkedList::showList() {

	struct Node *itr = head;

	if (itr == nullptr) {
		cout << "Empty List..!!!" << endl;
		return;
	}
	
	cout << "Number of elements - " << size << endl;
	while (itr) {
		cout << itr->mData << " ";
		itr = itr->next;
	}
	cout << endl << endl;

}

int main() {

	LinkedList list;

	cout << "Inserting " << 15 << " at Position 1" << endl;
	list.insertAt(1, 15);
	list.showList();

	cout << "Inserting "<< 25 <<" after 15" << endl;
	list.insertAfter(15, 25);
	list.showList();

	cout << "Inserting " << 35 << " at Position 2" << endl;
	list.insertAt(2, 35);
	list.showList();

	cout << "Inserting " << 20 << " at Position 4" << endl;
	list.insertAt(4, 20);
	list.showList();

	cout << "Inserting " << 30 << " at Position 3" << endl;
	list.insertAt(3, 30);
	list.showList();

	cout << "Inserting " << 45 <<" after 30" << endl;
	list.insertAfter(30, 45);
	list.showList();

	cout << "Inserting "<< 55 << " after 20" << endl;
	list.insertAfter(20, 55);
	list.showList();

	cout << "Deleting 15 " << endl;
	list.deleteElt(15);
	list.showList();

	cout << "Deleting 45 " << endl;
	list.deleteElt(45);
	list.showList();

	cout << "Deleting 55 " << endl;
	list.deleteElt(55);
	list.showList();

	cout << "Inserting " << 15 << " at Position 1" << endl;
	list.insertAt(1, 15);
	list.showList();

	cout << "Inserting " << 45 << " at Position 4" << endl;
	list.insertAt(4, 45);
	list.showList();

	cout << "Inserting " << 55 << " after 20" << endl;
	list.insertAfter(20, 55);
	list.showList();

	cout << "Deleting Element at Postion 1 " << endl;
	list.deleteAt(1);
	list.showList();

	cout << "Deleting Element at Postion 6 " << endl;
	list.deleteAt(6);
	list.showList();

	cout << "Deleting Element at Postion 3 " << endl;
	list.deleteAt(3);
	list.showList();

	return 0;
}