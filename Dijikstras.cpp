
#include <iostream>
#include <queue>
#include <list>
#include <functional>
#include <exception>
#include <iomanip>
#include <string>

using namespace std;

class Graph {
public:
	Graph(int vtx) : mVertices(vtx) {
		mEdges = new list<pair<int, int>>[vtx];
		if (mEdges == nullptr)
			throw exception("Memory Allocation Error..!!");

		path = new vector<int>[mVertices];
		if (path == nullptr)
			throw exception("Memory Allocation Error...!!");
	}

	void addEdge(int from, int to, int weight);
	void shortestPath(int source);
	void shortestPath(int source, int destn);
	void showPath(int, int);

private:
	list<pair<int, int>> *mEdges;
	const int mVertices;
	vector<int> *path;
};

void Graph::addEdge(int from, int to, int weight) {
	mEdges[from].push_back(make_pair(to, weight));
	mEdges[to].push_back(make_pair(from, weight));
}

void Graph::shortestPath(int source, int destn) {

	priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	vector<int> distance(mVertices, INT_MAX);

	pq.push(make_pair(0, source));
	distance[source] = 0;

	while (!pq.empty()) {

		int current = pq.top().second;
		pq.pop();

		for (auto itr = mEdges[current].begin(); itr != mEdges[current].end(); itr++) {
			int vertex = (*itr).first;
			int weight = (*itr).second;

			if (distance[vertex] > distance[current] + weight) {
				distance[vertex] = distance[current] + weight;
				pq.push(make_pair(distance[vertex], vertex));

				if (!path[vertex].empty())
					path[vertex].pop_back();
				path[vertex].push_back(current);
			}
		}
	}

	cout << "Vertex          Distance              Path             " << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << setw(3) << to_string(destn) << "\t\t" << setw(3) << distance[destn] << "\t\t";
	showPath(destn, source);
	cout << to_string(destn) << endl;
}

void Graph::shortestPath(int source) {

	priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	vector<int> distance(mVertices, INT_MAX);
	
	pq.push(make_pair(0, source));
	distance[source] = 0;

	while (!pq.empty()) {

		int current = pq.top().second;
		pq.pop();

		for (auto itr = mEdges[current].begin(); itr != mEdges[current].end(); itr++) {
			int vertex = (*itr).first;
			int weight = (*itr).second;
			
			if (distance[vertex] > distance[current] + weight) {
				distance[vertex] = distance[current] + weight;
				pq.push(make_pair(distance[vertex], vertex));
				
				if (!path[vertex].empty())
					path[vertex].pop_back();
				path[vertex].push_back(current);
			}
		}
	}

	//cout << "Shortest Paths from " << source << endl;
	cout << "Vertex          Distance              Path             " << endl;
	cout << "-------------------------------------------------------" << endl;
	for (int i = 0; i < mVertices; i++) {
		cout << setw(3) << i << "\t\t" << setw(3) << distance[i] << "\t\t";
		showPath(i, source);
		cout << i << endl;
	}
}

void Graph::showPath(int vertex, int source) {

	if (path[vertex].empty())
		return;

	if (path[vertex].back() == source) {
		cout << path[vertex].back() << " -> ";
		return;
	}
	else {
		showPath(path[vertex].back(), source);
		cout << path[vertex].back() << " -> ";
		return;
	}
	
}

int main() {

	Graph gph(9);

	gph.addEdge(0, 1, 4);
	gph.addEdge(0, 7, 8);
	gph.addEdge(1, 2, 8);
	gph.addEdge(1, 7, 11);
	gph.addEdge(2, 3, 7);
	gph.addEdge(2, 8, 2);
	gph.addEdge(2, 5, 4);
	gph.addEdge(3, 4, 9);
	gph.addEdge(3, 5, 14);
	gph.addEdge(4, 5, 10);
	gph.addEdge(5, 6, 2);
	gph.addEdge(6, 7, 1);
	gph.addEdge(6, 8, 6);
	gph.addEdge(7, 8, 7);

	gph.shortestPath(0, 8);

	return 0;
}