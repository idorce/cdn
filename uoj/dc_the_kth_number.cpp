//----------------------------------------------------------------------------//
// A. the kth number

// Problem description
// Find the kth largest element in an unsorted array A . Note that it is the kth largest element in the sorted order, not the kth distinct element. The range of length of A is N(1≤N≤5,000,000) and the element (integer) in A is no bigger than 10,000,00000.

// Input
// Line 1: the length of the unsorted array A and the index k. Line 2: the all elements in array A and split by spaces

// Output
// Line 1: A single integer that is the kth largest element in an unsorted array A.

// Sample Input 1
// 8 2
// 1 3 5 7 4 2 6 8
// Sample Output 1
// 7
// Sample Input 2
// 8 2
// 1 1 2 2 3 3 4 4
// Sample Output 2
// 4
//----------------------------------------------------------------------------//

#include <iostream>
#include <random>
#include <vector>

using namespace std;

default_random_engine generator;

int select(vector<int> &A, int k) {
    int p, n = A.size();
    vector<int> s, g;
    uniform_int_distribution<int> dist(0, n - 1);
    p = dist(generator);
    for (int i = n - 1; i >= 0; --i) {
        if (i == p) continue;
        if (A[i] > A[p])
            g.push_back(A[i]);
        else
            s.push_back(A[i]);
    }
    if (g.size() == k - 1)
        return A[p];
    else if (g.size() > k - 1)
        return select(g, k);
    else
        return select(s, k - g.size() - 1);
}

int main() {
    int len, k, a;
    vector<int> A;
    cin >> len >> k;
    while (len--) {
        scanf("%d", &a);
        A.push_back(a);
    }
    cout << select(A, k) << endl;
    return 0;
}