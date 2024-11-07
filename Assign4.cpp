#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

long long CountInvMerge(long long* a, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    long long* leftArr = new long long[n1];
    long long* rightArr = new long long[n2];
    
    for (int i = 0; i < n1; i++)
        leftArr[i] = a[left + i];
    for (int i = 0; i < n2; i++)
        rightArr[i] = a[mid + 1 + i];
    
    int i = 0, j = 0, k = left;
    long long inversions = 0;
    
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            a[k++] = leftArr[i++];
        } else {
            a[k++] = rightArr[j++];
            inversions += (n1 - i); 
        }
    }
    
    while (i < n1) {
        a[k++] = leftArr[i++];
    }
    
    while (j < n2) {
        a[k++] = rightArr[j++];
    }
    
    delete[] leftArr;
    delete[] rightArr;
    
    return inversions;
}

long long CountInv(long long* a, int left, int right) {
    long long inversions = 0;
    
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        inversions += CountInv(a, left, mid);
        inversions += CountInv(a, mid + 1, right);
        inversions += CountInvMerge(a, left, mid, right);
    }
    
    return inversions;
}

int main() {
    int n;
    while (cin >> n && n != 0) {
        long long* a = new long long[n];
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        long long inversions = CountInv(a, 0, n - 1);
        cout << inversions << endl;
        
        delete[] a;
    }
    return 0;
}
