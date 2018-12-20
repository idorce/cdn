//----------------------------------------------------------------------------//
// A. Cross the river

// Problem description:
// Some people want to cross a river by boat. Each person has a weight, and each boat can carry a maximum weight of limit. Each boat carries at most 2 people at the same time, provided the sum of the weight of those people is at most limit. Return the minimum number of boats to carry every given person. Note that it is guaranteed each person can be carried by a boat.

// Input:
// The input will be 3 lines. The first line is a single integer n (1 <= n <= 50000), which means the number of people. The second line is a single integer l (1 <= l <= 30000), represents the weight limit. And the last line contains n integers p_1, p_2, …, p_n (1 <= p_i <= l), separated by spaces, that represent people’s weights.

// Output:
// The output will consist of one line containing one integer, which represents the minimum number of boats.

// Sample Input:
// 4
// 3
// 3 2 2 1
// Sample Output:
// 3
//----------------------------------------------------------------------------//

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int n, l, w, boat = 0, i = 0, j;
    vector<int> ws;

    cin >> n >> l;
    j = n - 1;
    while (n--) {
        cin >> w;
        ws.push_back(w);
    }

    sort(ws.begin(), ws.end());

    while (i <= j) {
        if (ws[i] + ws[j] <= l) ++i;
        --j;
        ++boat;
    }

    cout << boat << endl;

    return 0;
}