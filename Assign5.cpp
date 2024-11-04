// GROUP:   2
// ID:      20226131
// Assign:  05
// Assign:  Kruskal
// UVA:     11631
// Name:    Mariam Mazen Mohamed Anwer

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>  
using namespace std;

struct DisjointSets
{
    int n;
    int* parent;
    int* num_nodes;

    void Initialize(int _n) {
        n = _n;
        parent = new int[n];
        num_nodes = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;      
            num_nodes[i] = 1;   
        }
    }

    void Destroy() {
        delete[] parent;
        delete[] num_nodes;
    }

    int Find(int i) {
        if (parent[i] != i)
            parent[i] = Find(parent[i]);  
        return parent[i];
    }

    bool Union(int i, int j) {
        int root_i = Find(i);
        int root_j = Find(j);
        if (root_i != root_j) {
            
            if (num_nodes[root_i] < num_nodes[root_j]) {
                parent[root_i] = root_j;
                num_nodes[root_j] += num_nodes[root_i];
            } else {
                parent[root_j] = root_i;
                num_nodes[root_i] += num_nodes[root_j];
            }
            return true;  
        }
        return false;  
    }
};

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b)) {
    int mid = n / 2;
    int i = 0, j = mid, k = 0;
    Type* temp = new Type[n];
    while (i < mid && j < n) {
        if (IsBefore(a[i], a[j])) temp[k++] = a[i++];
        else temp[k++] = a[j++];
    }
    while (i < mid) temp[k++] = a[i++];
    while (j < n) temp[k++] = a[j++];
    for (i = 0; i < n; i++) a[i] = temp[i];
    delete[] temp;
}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b)) {
    if (n <= 1) return;
    int mid = n / 2;
    MergeSort(a, mid, IsBefore);
    MergeSort(a + mid, n - mid, IsBefore);
    Merge(a, n, IsBefore);
}

struct Edge {
    int u, v, w;
};

bool IsBeforeEdge(Edge& a, Edge& b) {
    return a.w < b.w;
}

int main() {
    int m, n;
    while (true) {
        cin >> m >> n;
        if (m == 0 && n == 0) break;

        cout << "Number of junctions (m): " << m << ", Number of roads (n): " << n << endl;

        Edge* edges = new Edge[n];
        int total_weight = 0;

        for (int i = 0; i < n; i++) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
            total_weight += edges[i].w;
            cout << "Edge " << i+1 << ": (" << edges[i].u << ", " << edges[i].v 
                 << ") with weight " << edges[i].w << endl;
        }

        cout << "Total weight of all edges before MST: " << total_weight << endl;

        MergeSort(edges, n, IsBeforeEdge);

        DisjointSets ds;
        ds.Initialize(m);
        int mst_weight = 0;
        int edges_in_mst = 0;

        cout << "Processing edges to build MST..." << endl;

        for (int i = 0; i < n && edges_in_mst < m - 1; i++) {
            if (ds.Union(edges[i].u, edges[i].v)) {
                mst_weight += edges[i].w;
                edges_in_mst++;
                cout << "Added edge (" << edges[i].u << ", " << edges[i].v 
                     << ") with weight " << edges[i].w << " to MST" << endl;
            }
        }

        cout << "Total weight of MST: " << mst_weight << endl;
        cout << "Maximum daily savings: " << (total_weight - mst_weight) << endl;

        delete[] edges;
        ds.Destroy();
    }

    /*
    7 11
0 1 7
0 3 5
1 2 8
1 3 9
1 4 7
2 4 5
3 4 15
3 5 6
4 5 8
4 6 9
5 6 11
0 0

*/

    return 0;
}
