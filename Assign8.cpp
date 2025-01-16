#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>
using namespace std;

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b)) {
    int mid = n / 2;
    int i = 0, j = mid, k = 0;
    Type* temp = new Type[n];

    while (i < mid && j < n) {
        if (IsBefore(a[i], a[j])) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }
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

struct Point {
    double x, y;
};

bool IsBeforeX(Point& a, Point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool IsBeforeY(Point& a, Point& b) {
    return a.y < b.y || (a.y == b.y && a.x < b.x);
}

double dist(Point& a, Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double ClosestPair(Point* p, int n) {
    if (n <= 1) return 1e9; // Infinite distance for 1 point or less
    if (n == 2) return dist(p[0], p[1]); // Direct distance for 2 points

    int mid = n / 2;
    double midX = p[mid].x;

    // Divide the points
    double d1 = ClosestPair(p, mid);
    double d2 = ClosestPair(p + mid, n - mid);
    double d = min(d1, d2);

    // Combine step: handle strip points
    Point* strip = new Point[n];
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (fabs(p[i].x - midX) < d) strip[count++] = p[i];
    }
    MergeSort(strip, count, IsBeforeY);

    // Check distances in the strip
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count && (strip[j].y - strip[i].y) < d; j++) {
            d = min(d, dist(strip[i], strip[j]));
        }
    }

    delete[] strip;
    return d;
}

int main() {
    while (true) {
        int N;
        cin >> N;
        if (N == 0) break;

        Point* points = new Point[N];
        for (int i = 0; i < N; i++) {
            cin >> points[i].x >> points[i].y;
        }

        MergeSort(points, N, IsBeforeX);
        double result = ClosestPair(points, N);

        if (result >= 10000) {
            cout << "INFINITY" << endl;
        } else {
            printf("%.4f\n", result);
        }

        delete[] points;
    }
    return 0;
}
