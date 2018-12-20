//----------------------------------------------------------------------------//
// #6. Count Inversion

// Problem Description
// Recall the problem of finding the number of inversions. As in the course, we are given a sequence of n numbers a1,a2,⋯,an, and we define an inversion to be a pair i<j such that ai>aj.

// We motivated the problem of counting inversions as a good measure of how different two orderings are. However, one might feel that this measure is too sensitive. Let's call a pair a significant inversion if i<j and ai>3aj. Give an O(nlogn) algorithm to count the number of significant inversions between two orderings.

// The array contains N elements (1<=N<=100,000). All elements are in the range from 1 to 1,000,000,000.

// Input
// The first line contains one integer N, indicating the size of the array. The second line contains N elements in the array.

// 50% test cases guarantee that N < 1000.
// Output
// Output a single integer which is the number of pairs of significant inversions.

// Sample Inout
// 6
// 13 8 5 3 2 1
// Sample Output
// 6
//----------------------------------------------------------------------------//

#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

auto countInv(vector<long> A) {
    // base case
    if (A.size() == 1) return make_tuple(A, 0);

    int c1, c2, c, half_size = A.size() / 2;
    vector<long> L, R;
    tie(L, c1) = countInv(vector<long>(A.begin(), A.begin() + half_size));
    tie(R, c2) = countInv(vector<long>(A.begin() + half_size, A.end()));

    // merge
    int i = 0, j = 0, k = 0;
    while (i < L.size() && j < R.size()) {
        if (L[i] <= R[j])
            A[k++] = L[i++];
        else
            A[k++] = R[j++];
    }
    while (i < L.size()) A[k++] = L[i++];
    while (j < R.size()) A[k++] = R[j++];

    // count inversion
    c = i = j = 0;
    while (i < L.size() && j < R.size()) {
        if (L[i] > 3 * R[j]) {
            c += L.size() - i;
            ++j;
        } else
            ++i;
    }

    return make_tuple(A, c1 + c2 + c);
}

int main() {
    ios::sync_with_stdio(false);

    long N, a;
    vector<long> A;

    cin >> N;
    while (N--) {
        cin >> a;
        A.push_back(a);
    }

    cout << get<1>(countInv(A)) << endl;

    return 0;
}