
#include <iostream>
#include <vector>
#include <exception>
#include <queue>
#include <stack>

using namespace std;

template <typename T>
class Graph {
public:
	Graph(int vtx) :mVertices(vtx) {
		vtxCount = 0;
		mEdges = new vector<T>[mVertices];
		mVisited = new bool[mVertices];
		for (int i = 0; i < mVertices; i++)
			mVisited[i] = false;
	};
	~Graph() {};
	void dfs(T);
	void addEdges(T, T);
	int getVtxPos(T);
	void bfs(T);
	void dfsStack(T);
	void resetVisited();

private:
	int mVertices, vtxCount;
	vector<T> *mEdges;
	bool *mVisited;
};

template <typename T>
void Graph<T>::resetVisited() {
	for (int i = 0; i < mVertices; i++)
		mVisited[i] = false;
}

template <typename T>
int Graph<T>::getVtxPos(T elt) {

	for (int i = 0; i < vtxCount; i++) {
		if (mEdges[i][0] == elt) 
			return i;
	}
	
	return -1;
}

template <typename T>
void Graph<T>::addEdges(T vtx1, T vtx2) {

	bool found = false;

	if (vtxCount == 0) {
		mEdges[vtxCount].push_back(vtx1);
		mEdges[vtxCount++].push_back(vtx2);
		return;
	}

	for (int i = 0; i < vtxCount; i++) {
		if (mEdges[i][0] == vtx1) {
			mEdges[i].push_back(vtx2);
			found = true;
			return;
		}
	}

	if (!found) {
		mEdges[vtxCount].push_back(vtx1);
		mEdges[vtxCount++].push_back(vtx2);
	}
}

template <typename T>
void Graph<T>::dfs(T startVtx) {

	int pos = getVtxPos(startVtx);
	if (pos == -1)
		throw exception("Element not in Graph..!!");
	
	cout << startVtx << " ";
	mVisited[pos] = true;

	for (auto itr = mEdges[pos].begin(); itr != mEdges[pos].end(); itr++) {
		if (!mVisited[getVtxPos(*itr)])
			dfs(*itr);
	}
}

template <typename T>
void Graph<T>::dfsStack(T startVtx) {

	resetVisited();
	
	int pos = getVtxPos(startVtx);
	if (pos == -1)
		throw exception("Element not in Graph..!!");

	stack<T> stk;
	mVisited[pos] = true;
	stk.push(startVtx);

	while (!stk.empty()) {
		
		startVtx = stk.top();
		cout << startVtx << " ";
		stk.pop();

		int stVtxPos = getVtxPos(startVtx);
		for (auto itr = mEdges[stVtxPos].begin(); itr != mEdges[stVtxPos].end(); itr++) {
			pos = getVtxPos(*itr);
			if (!mVisited[pos]) {
				mVisited[pos] = true;
				stk.push(*itr);
			}
		}

	}
}

template <typename T>
void Graph<T>::bfs(T startVtx) {

	int pos = getVtxPos(startVtx);
	if (pos == -1)
		throw exception("Element not in Graph..!!");

	queue<T> adjQ;
	mVisited[pos] = true;
	adjQ.push(startVtx);

	while (!adjQ.empty()) {

		startVtx = adjQ.front();
		adjQ.pop();
		cout << startVtx << " ";
		int stVtxPos = getVtxPos(startVtx);
		for (auto itr = mEdges[stVtxPos].begin(); itr != mEdges[stVtxPos].end(); itr++) {
			pos = getVtxPos(*itr);
			if (!mVisited[pos]) {
				mVisited[pos] = true;
				adjQ.push(*itr);
			}
		}
	}

	resetVisited();
}


int main() {

	/*Graph<int> obj(4);

	obj.addEdges(0, 1);
	obj.addEdges(0, 2);
	obj.addEdges(1, 2);
	obj.addEdges(2, 0);
	obj.addEdges(2, 3);
	obj.addEdges(3, 3);

	obj.dfs(2);*/

	Graph<int> obj(6);

	obj.addEdges(1, 2);
	obj.addEdges(1, 3);
	obj.addEdges(2, 4);
	obj.addEdges(2, 5);
	obj.addEdges(3, 5);
	obj.addEdges(4, 5);
	obj.addEdges(4, 6);
	obj.addEdges(5, 6);
	obj.addEdges(6, 5);

	cout << "Breadth First Search" << endl;
	obj.bfs(1);

	cout << endl << "Depth First Search" << endl;
	obj.dfs(1);

	cout << endl << "Depth First Search - Stack" << endl;
	obj.dfsStack(1);

	return 0;
}
