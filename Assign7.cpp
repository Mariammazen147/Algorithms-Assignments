#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

template<class Value>
struct Array {
    int n, sz;
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
            for (int i = 0; i < n; ++i) newArr[i] = arr[i];
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

template<class Elem>
struct Heap {
    int* pos;
    Array<Elem> a;
    bool (*IsBefore)(Elem&, Elem&);

    void Initialize(bool (*_IsBefore)(Elem&, Elem&), int n) {
        IsBefore = _IsBefore;
        pos = new int[n];
        for (int i = 0; i < n; i++) pos[i] = -1;
        a.Initialize();
    }
    
    void Destroy() {
        delete[] pos;
        a.Destroy();
    }

    int Child(int i) { return 2 * i + 1; }
    int Parent(int i) { return (i - 1) / 2; }
    
    Elem GetFirst() { return a[0]; }
    
    Elem RetrieveFirst() {
        Elem top = a[0];
        pos[a[0].v] = -1;
        a[0] = a[--a.n];
        pos[a[0].v] = 0;
        MoveDown(0);
        return top;
    }

    void Add(Elem e) {
        pos[e.v] = a.n;
        a.AddLast(e);
        MoveUp(a.n - 1);
    }

    void MoveUp(int i) {
        while (i > 0 && IsBefore(a[i], a[Parent(i)])) {
            swap(a[i], a[Parent(i)]);
            pos[a[i].v] = i;
            i = Parent(i);
        }
        pos[a[i].v] = i;
    }

    void MoveDown(int i) {
        while (true) {
            int left = Child(i), right = left + 1, smallest = i;
            if (left < a.n && IsBefore(a[left], a[i])) smallest = left;
            if (right < a.n && IsBefore(a[right], a[smallest])) smallest = right;
            if (smallest == i) break;
            swap(a[i], a[smallest]);
            pos[a[i].v] = i;
            pos[a[smallest].v] = smallest;
            i = smallest;
        }
    }
};

struct Edge {
    int v;
    int w;
};

struct Node {
    Array<Edge> adj;

    void Initialize() { adj.Initialize(); }
    void Destroy() { adj.Destroy(); }
};

struct Graph {
    int n;
    Node* nodes;

    void Initialize(int _n) {
        n = _n;
        nodes = new Node[n];
        for (int i = 0; i < n; ++i) nodes[i].Initialize();
    }

    void Destroy() {
        for (int i = 0; i < n; ++i) nodes[i].Destroy();
        delete[] nodes;
    }
};

struct Elem {
    int v, w;

    Elem(int _v = 0, int _w = 0) : v(_v), w(_w) {}
};

bool IsBefore(Elem& a, Elem& b) {
    return a.w < b.w;
}

void Dijkstra(Graph& graph, int src, int dst) {
    Array<int> dist;
    dist.Initialize();
    dist.n = graph.n;
    for (int i = 0; i < graph.n; ++i) dist[i] = 1e9;
    dist[src] = 0;

    Heap<Elem> heap;
    heap.Initialize(IsBefore, graph.n);
    heap.Add(Elem(src, 0));

    while (heap.a.n > 0) {
        Elem u = heap.RetrieveFirst();
        if (u.v == dst) {
            cout << u.w << endl;
            dist.Destroy();
            heap.Destroy();
            return;
        }
        for (int i = 0; i < graph.nodes[u.v].adj.n; ++i) {
            Edge e = graph.nodes[u.v].adj[i];
            if (dist[u.v] + e.w < dist[e.v]) {
                dist[e.v] = dist[u.v] + e.w;
                heap.Add(Elem(e.v, dist[e.v]));
            }
        }
    }
    cout << "unreachable" << endl;
    dist.Destroy();
    heap.Destroy();
}

int main() {
    int cases;
    cin >> cases;
    for (int x = 1; x <= cases; ++x) {
        int n, m, S, T;
        cin >> n >> m >> S >> T;
        Graph graph;
        graph.Initialize(n);
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            graph.nodes[u].adj.AddLast({v, w});
            graph.nodes[v].adj.AddLast({u, w});
        }
        cout << "Case #" << x << ": ";
        Dijkstra(graph, S, T);
        graph.Destroy();
    }
    return 0;
}
