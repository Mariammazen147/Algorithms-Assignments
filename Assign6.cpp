#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

template<class Value>
struct Array {
    int n, sz;
    Value* arr;

    void Initialize() {
        n = 0;
        sz = 2;
        arr = new Value[sz];
    }

    void Destroy() {
        delete[] arr;
    }

    void AddLast(Value v) {
        if (n == sz) {
            sz *= 2;
            Value* newArr = new Value[sz];
            for (int i = 0; i < n; i++) {
                newArr[i] = arr[i];
            }
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

struct Edge {
    int v;      
    double w;   
};

struct Node {
    int x, y;        
    Array<Edge> adj; 

    void Initialize() {
        adj.Initialize();
    }

    void Destroy() {
        adj.Destroy();
    }
};

struct Graph {
    int n;
    Node* nodes;

    void Initialize(int _n) {
        n = _n;
        nodes = new Node[n];
        for (int i = 0; i < n; i++) {
            nodes[i].Initialize();
        }
    }

    void Destroy() {
        for (int i = 0; i < n; i++) {
            nodes[i].Destroy();
        }
        delete[] nodes;
    }
};

double Sqrt(double v, int n = 100) {
    double x = v;
    for (int i = 0; i < n; i++) {
        x = 0.5 * (x + v / x);
    }
    return x;
}

double distance(int x1, int y1, int x2, int y2) {
    return Sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double Prim(Graph& graph) {
    vector<bool> visited(graph.n, false);
    vector<double> maxEdge(graph.n, 1e9);
    maxEdge[0] = 0;
    double maxDist = 0.0;

    using EdgePair = pair<double, int>;
    priority_queue<EdgePair, vector<EdgePair>, greater<EdgePair>> pq;
    pq.push({0, 0});

    while (!pq.empty()) {
        double weight = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;
        maxDist = max(maxDist, weight);

        for (int i = 0; i < graph.nodes[u].adj.n; i++) {
            Edge& edge = graph.nodes[u].adj[i];
            int v = edge.v;
            if (!visited[v] && edge.w < maxEdge[v]) {
                maxEdge[v] = edge.w;
                pq.push({edge.w, v});
            }
        }
    }
    return maxDist;
}

int main() {
    int n, caseNo = 1;
    while (cin >> n && n != 0) {
        Graph graph;
        graph.Initialize(n);

        for (int i = 0; i < n; i++) {
            cin >> graph.nodes[i].x >> graph.nodes[i].y;
        }

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double dist = distance(graph.nodes[i].x, graph.nodes[i].y, graph.nodes[j].x, graph.nodes[j].y);
                graph.nodes[i].adj.AddLast({j, dist});
                graph.nodes[j].adj.AddLast({i, dist});
            }
        }

        double frogDistance = Prim(graph);
        cout << "Scenario #" << caseNo++ << endl;
        cout << fixed << setprecision(3) << "Frog Distance = " << frogDistance << endl << endl;

        graph.Destroy();
    }
    return 0;
}
