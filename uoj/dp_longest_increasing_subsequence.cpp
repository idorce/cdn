//----------------------------------------------------------------------------//
// A. Longest Increasing Subsequence

// DescriptionA numeric sequence of ai is increasing if a1<a2<⋯<aN. Let the subsequence of the given numeric sequence (a1,a2,…,aN) be any sequence (ai1,ai2,...,aiK), where 1<=i1<i2<⋯<iK<=N. For example, sequence (1,7,3,5,9,4,8) has increasing subsequences, e. g., (1,7), (3,4,8) and many others. The longest increasing subsequence is of length 4, e. g., (1,3,5,8).

// Your program, when given the numeric sequence, must find the length of its longest increasing subsequence.

// Input
// The first line of input is T, which means there are T groups test cases. For each test case, the first line contains the length of sequence N, and the second line contains the elements of sequence - N integers in the range from 0 to 1000000 each, separated by spaces(1 <= N <= 100000).

// Output
// Output file must contain T integers - each integer represents he length of the longest increasing subsequence of the given sequence.

// Sample Input
// 2
// 4
// 1 2 3 1
// 7
// 1 7 3 5 9 4 8
// Sample Output
// 3
// 4
//----------------------------------------------------------------------------//

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

//int LIS(vector<int> &s) {
//    int maxLen = 1;
//    vector<int> c(s.size(), 1);
//    for (int i = 1; i < s.size(); ++i) {
//        for (int j = i - 1; j >= 0; --j) {
//            if (s[j] < s[i]) c[i] = max(c[i], c[j] + 1);
//        }
//        maxLen = max(maxLen, c[i]);
//    }
//    return maxLen;
//}

// 长度为i的LIS的最小末尾,构成的数组

int LIS(vector<int> &s) {
    vector<int> c;
    for (int n : s) {
        // binary search for upper bound
        int l = 0, h = c.size(), m;
        while (l < h) {
            m = (l + h) / 2;
            if (c[m] < n)
                l = m + 1;
            else
                h = m;
        }
        if (l == c.size())
            c.push_back(n);
        else
            c[l] = n;
    }
    return c.size();
}

int main() {
    ios::sync_with_stdio(false);

    int T, N, n;
    vector<int> Ls, s;
    cin >> T;
    while (T--) {
        cin >> N;
        s.clear();
        while (N--) {
            cin >> n;
            s.push_back(n);
        }
        Ls.push_back(LIS(s));
    }

    for (auto L : Ls) cout << L << endl;

    return 0;
}