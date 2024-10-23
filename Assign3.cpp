// GROUP:   2
// ID:      20226131
// Assign:  03
// Assign:  Graphs
// UVA:     924
// Name:    Mariam Mazen Mohamed Anwer

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

template<class Value>
struct Array
{
	int  n, sz;
	Value* arr;

	void Initialize() {
		n = 0;
		sz = 1;
		arr = new Value[sz];
	}

	void Destroy() {
		delete[] arr;
	}

	void AddLast(Value v) {
		if (n == sz) {
			sz *= 2;
			Value* newArr = new Value[sz];
			for (int i = 0; i < n; i++)
				newArr[i] = arr[i];
			delete[] arr;
			arr = newArr;
		}
		arr[n++] = v;
	}

	void RemoveLast() {
		if (n > 0) n--;
	}

	Value& operator[](int i) {
		return arr[i];
	}
};

struct Node
{
	Array<int> adj;

	void Initialize() {
		adj.Initialize();
	}

	void Destroy() {
		adj.Destroy();
	}
};

struct Graph
{
	int n;
	Node* nodes;

	void Initialize(int _n) {
		n = _n;
		nodes = new Node[n];
		for (int i = 0; i < n; i++)
			nodes[i].Initialize();
	}

	void Destroy() {
		for (int i = 0; i < n; i++)
			nodes[i].Destroy();
		delete[] nodes;
	}
};

template <class Type>
struct Queue
{
	int f, n, sz;
	Type* elems;

	void Initialize(int size) {
		f = 0;
		n = 0;
		sz = size;
		elems = new Type[sz];
	}

	void Destroy() {
		delete[] elems;
	}

	void Add(Type t) {
		elems[(f + n) % sz] = t;
		n++;
	}

	Type Pop() {
		Type t = elems[f];
		f = (f + 1) % sz;
		n--;
		return t;
	}

	Type Peek() {
		return elems[f];
	}

	int Num() {
		return n;
	}
};

void BFS(Graph& g, int source) {
	Queue<int> q;
	q.Initialize(g.n);
	int* visited = new int[g.n];
	int* day = new int[g.n];
	int* dailyBoom = new int[g.n];

	memset(visited, 0, sizeof(int) * g.n);
	memset(dailyBoom, 0, sizeof(int) * g.n);

	visited[source] = 1;
	day[source] = 0;
	q.Add(source);

	int maxBoom = 0, firstDay = -1;

	while (q.Num() > 0) {
		int u = q.Pop();
		for (int i = 0; i < g.nodes[u].adj.n; i++) {
			int v = g.nodes[u].adj[i];
			if (!visited[v]) {
				visited[v] = 1;
				day[v] = day[u] + 1;
				q.Add(v);
				dailyBoom[day[v]]++;

				if (dailyBoom[day[v]] > maxBoom) {
					maxBoom = dailyBoom[day[v]];
					firstDay = day[v];
				}
			}
		}
	}

	if (maxBoom == 0) {
		cout << "Output: 0 (No boom beyond the source)" << endl;
	} else {
		cout << "Output: Maximum boom size: " << maxBoom << ", First boom day: " << firstDay << endl;
	}

	q.Destroy();
	delete[] visited;
	delete[] day;
	delete[] dailyBoom;
}

int main()
{
	int E;

	// Input the number of employees
	cout << "Enter the number of employees (E): ";
	cin >> E;

	Graph g;
	g.Initialize(E);

	// Input the friendship relations for each employee
	for (int i = 0; i < E; i++) {
		cout << "Enter the number of friends for employee " << i << " followed by their IDs: ";
		int N;
		cin >> N;
		for (int j = 0; j < N; j++) {
			int friendID;
			cin >> friendID;
			g.nodes[i].adj.AddLast(friendID);
		}
	}

	int T;

	// Input the number of test cases
	cout << "Enter the number of test cases (T): ";
	cin >> T;

	// For each test case, input the source employee and perform BFS
	for (int i = 0; i < T; i++) {
		int source;
		cout << "Enter the source employee ID for test case " << i + 1 << ": ";
		cin >> source;
		cout << "Test case " << i + 1 << ": Source employee is " << source << endl;
		BFS(g, source);
	}

	g.Destroy();
	return 0;
}
