//----------------------------------------------------------------------------//
// B. minimum distance

// Problem description
// Given N(2<=N<=100,000) points on the plane, find the nearest two points, print the minimum distance.

// Input
// Line 1: an integer N, stands for the total number of points. N lines follow: each line contains a pair of (x, y) which are the coordinates of a point and splited by spaces, each value is no bigger than 1,000,000,000.

// Output
// Line1: the minimum distance, accurate up to 2 decimal places.

// Sample Input 1
// 2
// 0 0.5
// 0 0.5
// Sample Output 1
// 0.00
// Sample Input 2
// 3
// 0 1
// -1 1
// -1 0
// Sample Output 2
// 1.00
//----------------------------------------------------------------------------//

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <tuple>
#include <vector>

using namespace std;

struct point {
    double x, y;
};

vector<point> D;
double INF = numeric_limits<double>::infinity();

double dist(int i, int j) {
    return sqrt(pow(D[i].x - D[j].x, 2) + pow(D[i].y - D[j].y, 2));
}

double comp_11(vector<int> comp) {
    double d = INF;
    for (int i = comp.size() - 1; i > 0; --i) {
        for (int j = i - 1; j >= 0 && j >= i - 11; --j) {
            d = min(d, dist(comp[i], comp[j]));
        }
    }
    return d;
}

tuple<vector<int>, double> merge(vector<int> &l, vector<int> &r, double x_l, double x_r) {
    vector<int> y(l.size() + r.size()), comp;
    int i = l.size() - 1, j = r.size() - 1, k = y.size() - 1;
    while (i >= 0 && j >= 0) {
        if (D[l[i]].y > D[r[j]].y) {
            if (D[l[i]].x >= x_l && D[l[i]].x <= x_r) comp.push_back(l[i]);
            y[k--] = l[i--];
        } else {
            if (D[r[j]].x >= x_l && D[r[j]].x <= x_r) comp.push_back(r[j]);
            y[k--] = r[j--];
        }
    }
    while (i >= 0) {
        if (D[l[i]].x >= x_l && D[l[i]].x <= x_r) comp.push_back(l[i]);
        y[k--] = l[i--];
    }
    while (j >= 0) {
        if (D[r[j]].x >= x_l && D[r[j]].x <= x_r) comp.push_back(r[j]);
        y[k--] = r[j--];
    }
    return make_tuple(y, comp_11(comp));
}

tuple<double, vector<int>> closest(int l, int r) {
    int m = (r - l) / 2 + l;
    double d, d_l, d_r, x_m, d_m;
    vector<int> by_y, by_y_l, by_y_r;
    if (l == r) {
        return make_tuple(INF, vector<int>{l});
    }
    if (r - l == 1) {
        if (D[l].y <= D[r].y)
            by_y = vector<int>{l, r};
        else
            by_y = vector<int>{r, l};
        return make_tuple(dist(l, r), by_y);
    }
    tie(d_l, by_y_l) = closest(l, m);
    tie(d_r, by_y_r) = closest(m + 1, r);
    d = min(d_l, d_r);
    x_m = (D[m].x + D[m + 1].x) / 2.0;
    tie(by_y, d_m) = merge(by_y_l, by_y_r, x_m - d, x_m + d);
    return make_tuple(min(d, d_m), by_y);
}

int main() {
    int N;
    double x, y;
    cin >> N;
    while (N--) {
        scanf("%lf %lf", &x, &y);
        D.push_back(point{x, y});
    }
    sort(D.begin(), D.end(), [](point a, point b) { return a.x < b.x; });
    printf("%.2lf", get<0>(closest(0, D.size() - 1)));
    return 0;
}