#include <bits/stdc++.h>
using namespace std;

string a, b;
int offset, steps;

void print(int i, int j, vector<vector<int>>& dp) {
    if (i == 0 && j == 0) return;
    else if (i != 0 && j != 0 && a[i - 1] == b[j - 1]) {
        print(i - 1, j - 1, dp);
    } else if (j != 0 && dp[i][j] == dp[i][j - 1] + 1) {
        print(i, j - 1, dp);
        offset++;
        printf("%d Insert %d,%c\n", ++steps, i + offset, b[j - 1]);
    } else if (i != 0 && dp[i][j] == dp[i - 1][j] + 1) {
        print(i - 1, j, dp);
        printf("%d Delete %d\n", ++steps, i + offset);
        offset--;
    } else if (dp[i][j] == dp[i - 1][j - 1] + 1) {
        print(i - 1, j - 1, dp);
        printf("%d Replace %d,%c\n", ++steps, i + offset, b[j - 1]);
    }
}

int main() {
    bool printed = false;

    // Use freopen to redirect input from a file
    freopen("input_assign11_00526.txt", "r", stdin);  // Open "input.txt" for reading from stdin

    while (getline(cin, a)) {  // Read string a from the file
        if (printed) printf("\n");
        printed = true;
        getline(cin, b);  // Read string b from the file

        // Initialize DP table
        vector<vector<int>> dp(a.length() + 1, vector<int>(b.length() + 1));
        for (int i = 0; i <= b.length(); i++) dp[0][i] = i;

        // Fill DP table with minimum edit distances
        for (int i = 0; i < a.length(); i++) {
            dp[i + 1][0] = i + 1;
            for (int j = 0; j < b.length(); j++) {
                if (a[i] == b[j]) {
                    dp[i + 1][j + 1] = dp[i][j];
                } else {
                    dp[i + 1][j + 1] = min(dp[i][j], 
                                            min(dp[i][j + 1], dp[i + 1][j])) + 1;
                }
            }
        }

        // Output the minimum edit distance
        printf("%d\n", dp[a.length()][b.length()]);
        offset = steps = 0;

        // Print the sequence of operations
        print(a.length(), b.length(), dp);
    }

    fclose(stdin);  // Close the file input stream
    return 0;
}
