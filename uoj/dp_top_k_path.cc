//----------------------------------------------------------------------------//
// B. Top k path

// Description
// A robot is located at the top-left corner of a m×n grid. The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid. There is a non-negative integer in each small grid which means the score that the robot get when it passes this grid. Now you need to calculate the top k total scores when the robot reach the destination.

// Note: The top k total scores may contain same total score got from different paths.

// Input
// The first line of input are m and n,which denote the size of the grid. The second line of input is the k. The next m lines are the score matrix. (1≤m,n,k≤100,and 0≤score≤100)

// Output
// There is only one line in the Output,which is a descending sequence consist of the top k total scores.

// Sample1
// Input

// 3 3
// 2
// 3 2 5
// 3 2 2
// 4 2 1
// Output

// 13 13
// Sample2
// Input

// 4 3
// 3
// 7 1 5
// 4 6 2
// 4 2 1
// 5 7 3
// Output

// 30 29 27
//----------------------------------------------------------------------------//

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int m, n, k, s;
    cin >> m >> n >> k;

    auto g = vector<vector<vector<int>>>(m,
                                         vector<vector<int>>(n, vector<int>()));

    // top-left cell
    cin >> s;
    g[0][0].push_back(s);

    // left cells of first row
    for (int j = 1; j < n; ++j) {
        cin >> s;
        g[0][j].push_back(g[0][j - 1][0] + s);
    }

    // left rows
    for (int i = 1; i < m; ++i) {
        // first cell
        cin >> s;
        g[i][0].push_back(g[i - 1][0][0] + s);

        // left cells
        for (int j = 1; j < n; ++j) {
            cin >> s;
            int r, p, q;
            auto left = g[i][j - 1], up = g[i - 1][j];
            r = p = q = 0;
            for (; p < left.size() && q < up.size() && r < k; ++r) {
                if (left[p] > up[q])
                    g[i][j].push_back(left[p++] + s);
                else
                    g[i][j].push_back(up[q++] + s);
            }
            for (; p < left.size() && r < k; ++r)
                g[i][j].push_back(left[p++] + s);
            for (; q < up.size() && r < k; ++r)
                g[i][j].push_back(up[q++] + s);
        }
    }

    auto topk = g[m - 1][n - 1];
    int i = 0;
    for (; i < topk.size() - 1;) cout << topk[i++] << ' ';
    cout << topk[i] << endl;

    return 0;
}