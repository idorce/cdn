// From other sources.
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <algorithm>
#include <iostream>
using namespace std;

int s[5], t[5], low = 0, high = 24, scale = 100000, mid;
float si, ti;
void _bound() {
    low = 24 * scale;
    high = -1;
    for (int i = 1; i < 5; ++i) {
        low = min(low, s[i] - t[i - 1]);
        high = max(high, t[i] - s[i - 1]);
    }
}
bool _check(int dist) {
    int land = s[0];
    for (int i = 1; i < 5; ++i) {
        land = max(s[i], land + dist);
        if (land > t[i])
            return false;
    }
    return true;
}
void solve(float dist) {
    float land = float(s[0]) / scale;
    printf("%.2f ", land);
    for (int i = 1; i < 4; ++i) {
        land = max(float(s[i]) / scale, land + dist);
        printf("%.2f ", land);
    }
    printf("%.2f\n", max(land + dist, float(s[4]) / scale));
}
int main() {
    for (int i = 0; i < 5; ++i) {
        scanf("%f%f", &si, &ti);
        s[i] = si * scale;
        t[i] = ti * scale;
    }
    _bound();
    while (low <= high) {
        mid = (low + high) / 2;
        if (_check(mid))
            low = mid + 1;
        else
            high = mid - 1;
    }
    float dist = float(mid) / float(scale);
    solve(dist);
    //system("pause");
    return 0;
}
