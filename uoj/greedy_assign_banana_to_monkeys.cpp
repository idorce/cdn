//----------------------------------------------------------------------------//
// B. Assign banana to monkeys

// Problem description:
// There are N Monkeys and N bananas are placed in a straight line. Each monkey want to have a banana, if two monkeys want to own the same banana, there will be a fight! A monkey can stay at his position, move one step right from x to x + 1, or move one step left from x to x -1. Any of these moves consumes 1 second. Assign monkeys to banana so that not monkey fight each other and the time when the last monkey gets a banana is minimized.

// Input:
// The input contain two arrays of int. The first array is the positions of monkeys. The second array is the positions of bananas.

// Output:
// The output is a int, which is the time(in seconds) it takes when all bananas are assigned to monkeys.

// Sample input:
// 1 3 6
// 2 4 6
// Sample output:
// 1
// Sample explanation:
// Assign monkey at position 1 to banana at position 2. (1 second)

// Assign monkey at position 3 to banana at position 4. (1 second)

// Assign monkey at position 6 to banana at position 6. (0 second)

// Overall time is max(1, 1, 0) = 1 second.
//----------------------------------------------------------------------------//

#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    string l;
    int x;
    vector<int> b, m;

    getline(cin, l);
    istringstream in(l);
    while (in >> x) b.push_back(x);
    sort(b.begin(), b.end());

    getline(cin, l);
    in.clear();
    in.str(l);
    while (in >> x) m.push_back(x);
    sort(m.begin(), m.end());

    int maxt = 0;
    for (int i = m.size() - 1; i >= 0; --i)
        maxt = max(maxt, abs(m[i] - b[i]));

    cout << maxt << endl;

    return 0;
}