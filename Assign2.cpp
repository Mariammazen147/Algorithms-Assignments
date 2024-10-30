// GROUP:   2
// ID:      20226131
// Assign:  02
// Assign:  DisjointSets
// UVA:     10608
// Name:    Mariam Mazen Mohamed Anwer

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

struct DisjointSets
{
    int n;
    int* parent;
    int* num_nodes;

    void Initialize(int _n)
    {
        n = _n;
        parent = new int[n + 1];
        num_nodes = new int[n + 1];
        for (int i = 1; i <= n; i++)
        {
            parent[i] = i; 
            num_nodes[i] = 1; 
        }
    }

    void Destroy()
    {
        delete[] parent;
        delete[] num_nodes;
    }

    int Find(int i)
    {
        if (parent[i] != i) 
        {
            parent[i] = Find(parent[i]);
        }
        return parent[i];
    }

    bool Union(int i, int j)
    {
        int root_i = Find(i);
        int root_j = Find(j);

        if (root_i != root_j)
        {
            if (num_nodes[root_i] < num_nodes[root_j]) 
            {
                parent[root_i] = root_j;
                num_nodes[root_j] += num_nodes[root_i];
            }
            else
            {
                parent[root_j] = root_i;
                num_nodes[root_i] += num_nodes[root_j];
            }
            return true;
        }
        return false;
    }

    int GetMaxSize()
    {
        int max_size = 0;
        for (int i = 1; i <= n; i++)
        {
            if (parent[i] == i) 
            {
                max_size = max(max_size, num_nodes[i]);
            }
        }
        return max_size;
    }
};

int main()
{
    int t;
    cout << "Enter number of test cases: ";
    cin >> t; 
    while (t--)
    {
        int N, M;
        cout << "Enter number of citizens (N) and number of friendships (M): ";
        cin >> N >> M;
        DisjointSets ds;
        ds.Initialize(N);
        
        cout << "Enter " << M << " pairs of friendships:\n";
        for (int i = 0; i < M; i++)
        {
            int A, B;
            cout << "Friendship pair " << i + 1 << ": ";
            cin >> A >> B;
            ds.Union(A, B);
        }

        cout << "Largest group of friends: " << ds.GetMaxSize() << endl;
        ds.Destroy();
    }
    return 0;
}

//2 3 2 1 2 2 3 10 12 1 2 3 1 3 4 5 4 3 5 4 6 5 2 2 1 7 1 1 2 9 10 8 9

//3 7 