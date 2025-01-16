#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Obj
{
    int v; // price of object
    int w; // weight of object
};

Obj a[1000];

////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Recursive with memoization
int T1[1001][31];
int Knapsack1(int n, int w) {
    if (n == 0 || w == 0) return 0;
    if (T1[n][w] != -1) return T1[n][w];
    if (a[n - 1].w > w)
        return T1[n][w] = Knapsack1(n - 1, w);
    else
        return T1[n][w] = max(Knapsack1(n - 1, w), a[n - 1].v + Knapsack1(n - 1, w - a[n - 1].w));
}

int ComputeKnapsack1(int N, int W) {
    memset(T1, -1, sizeof(T1));
    return Knapsack1(N, W);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Bottom up Dynamic programming 2D
int T2[1001][31];
int ComputeKnapsack2(int N, int W) {
    memset(T2, 0, sizeof(T2));
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= W; j++) {
            if (a[i - 1].w > j)
                T2[i][j] = T2[i - 1][j];
            else
                T2[i][j] = max(T2[i - 1][j], a[i - 1].v + T2[i - 1][j - a[i - 1].w]);
        }
    }
    return T2[N][W];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Bottom Up Dynamic Programming 2 Rows
int T3[2][31];
int ComputeKnapsack3(int N, int W) {
    memset(T3, 0, sizeof(T3));
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= W; j++) {
            if (a[i - 1].w > j)
                T3[i % 2][j] = T3[(i - 1) % 2][j];
            else
                T3[i % 2][j] = max(T3[(i - 1) % 2][j], a[i - 1].v + T3[(i - 1) % 2][j - a[i - 1].w]);
        }
    }
    return T3[N % 2][W];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Bottom Up Dynamic Programming 1D
int T4[31];
int ComputeKnapsack4(int N, int W) {
    memset(T4, 0, sizeof(T4));
    for (int i = 1; i <= N; i++) {
        for (int j = W; j >= a[i - 1].w; j--) {
            T4[j] = max(T4[j], a[i - 1].v + T4[j - a[i - 1].w]);
        }
    }
    return T4[W];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeKnapsack(int N, int W) {
    //return ComputeKnapsack1(N, W);
    //return ComputeKnapsack2(N, W);
    //return ComputeKnapsack3(N, W);
    return ComputeKnapsack4(N, W);
}

void Compute() {
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        for (int i = 0; i < N; i++) {
            cin >> a[i].v >> a[i].w;
        }

        int G, maxValue = 0;
        cin >> G;
        while (G--) {
            int MW;
            cin >> MW;
            maxValue += ComputeKnapsack(N, MW);
        }
        cout << maxValue << endl;
    }
}


int main() {
    freopen("input_assign09_10130.txt", "r", stdin);
    Compute();
    return 0;
}
