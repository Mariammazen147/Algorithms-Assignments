#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits.h>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int p[11];         // Dimensions of matrices
int T[11][11];     // T[a][b] = optimal number of multiplications for p[a]...p[b]
int D[11][11];     // D[a][b] = decision (value of k) for optimal split between p[a]...p[b]

// Top-down version
int MatChain(int a, int b) {
    if (T[a][b] != -1) return T[a][b]; // Return cached value if already computed
    if (a + 1 == b) return T[a][b] = 0; // Base case: no multiplication needed for single matrix
    
    int min_cost = INT_MAX;
    for (int k = a + 1; k < b; ++k) {
        int cost = MatChain(a, k) + MatChain(k, b) + p[a] * p[k] * p[b];
        if (cost < min_cost) {
            min_cost = cost;
            D[a][b] = k; // Store optimal k for splitting
        }
    }
    return T[a][b] = min_cost;
}

void MatChainTopDown(int n) {
    memset(T, -1, sizeof(T)); // Initialize memoization table
    MatChain(0, n);
}

// Bottom-up version
void MatChainBottomUp(int n) {
    memset(T, 0, sizeof(T)); // Initialize T with 0
    for (int length = 2; length <= n; ++length) { // Length of chain segment
        for (int i = 0; i <= n - length; ++i) {
            int j = i + length;
            T[i][j] = INT_MAX;
            for (int k = i + 1; k < j; ++k) {
                int cost = T[i][k] + T[k][j] + p[i] * p[k] * p[j];
                if (cost < T[i][j]) {
                    T[i][j] = cost;
                    D[i][j] = k; // Store decision point
                }
            }
        }
    }
}

// Output the solution recursively
void MatChainSol(int a, int b) {
    if (a + 1 == b) {
        cout << "A" << a + 1; // Single matrix
        return;
    }
    cout << "(";
    MatChainSol(a, D[a][b]);  // Left segment
    cout << " x ";
    MatChainSol(D[a][b], b);  // Right segment
    cout << ")";
}

void Compute() {
    int case_no = 1;
    while (true) {
        int n;
        cin >> n; // Number of matrices
        if (n == 0) break;

        for (int i = 0; i < n; ++i) {
            cin >> p[i] >> p[i + 1]; // Input dimensions
        }

        MatChainBottomUp(n); // Use bottom-up approach
        cout << "Case " << case_no++ << ": ";
        MatChainSol(0, n);   // Output solution
        cout << endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    freopen("input_assign10_00348.txt", "r", stdin);
    Compute();
    return 0;
}
