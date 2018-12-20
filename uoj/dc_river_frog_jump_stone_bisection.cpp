//----------------------------------------------------------------------------//
// #5. river

// Description
// Two lovely frogs Alice and Bob live by a river. There are several stones in this river. Every morning, they will go to the other side of the river to have fun. They cross the river by jumping from one stone to another. One day, Alice decides to play tricks on Bob. She plans to remove some stones so that there is no “easy jump” for Bob to across the river any more. But she has no idea which stones she should remove. She needs your help.

// The width of the river is an integer L((1≤L≤1,000,000,000). We treat the river as a one-dimensional line segment,with two endpoints A (two frog’s home) and B (the other side of the river). Among the river, there are N stones (0≤N≤50,000). The distance from the i-th stone to side A is Di (0<Di<L). Alice would like to remove M stones in the river (0≤M≤N) so that with the rest of the stones, the minimum distance among all possible jumps for Bob is the largest.

// Input
// Each instance contains two lines. The first line contains three integers L, N and M. The second line gives the positions of N stones. No two stones share the same position.

// 30% test cases guarantee that N < 20.
// Output
// For each instance, output a single line with a single integer which is the maximum of the minimum distance among all possible jumps after removing M stones. In the example, Alice should remove stones with distance 2 and 14. After removing these two stones, the minimum distance of jumps is 4, and there are two jumps with distance 4: from 17 to 21, and from 21 to 25.

// Sample Input
// 25 5 2
// 2 14 11 21 17
// Sample Output
// 4

// WD Xu：
// 最大值最小，最小值最大。看一眼就知道要二分。大概率二分。
// 先观察一波单调性，如果单调的话。
//----------------------------------------------------------------------------//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int L, N, M, s;
    vector<int> S;
    cin >> L >> N >> M;
    while (N--) {
        cin >> s;
        S.push_back(s);
    }

    sort(S.begin(), S.end());
    S.push_back(L);

    int l = 0, h = L, m, cur, move;
    while (l <= h) {
        cur = move = 0;
        m = (l + h) / 2;
        for (auto s : S) {
            if (s - cur < m) ++move;
            else cur = s;
        }
        if (move > M) h = m - 1;
        else l = m + 1;
    }

    cout << h << endl;

    return 0;
}