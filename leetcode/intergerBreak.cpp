#include <cmath>
#include <cstdlib>
using namespace std;

class Solution {
   public:
    int integerBreak(int n) {
        if (n == 2) return 1;
        if (n == 3) return 2;
        auto r = div(n, 3);
        if (r.rem == 0) return pow(3, r.quot);
        if (r.rem == 1) return pow(3, r.quot - 1) * 4;
        if (r.rem == 2) return pow(3, r.quot) * 2;
    }
};