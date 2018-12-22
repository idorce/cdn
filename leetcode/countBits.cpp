// hmm. Relation found by deduction...
vector<int> countBits(int num) {
    vector<int> v(num + 1, 0);
    int shift;        
    for (int n = 1; n <= num; ++n) {
        if ((n&(n-1)) == 0) shift = n;
        v[n] = 1 + v[n - shift];
    }
    return v;
}

// There are several methods.

// Remove rightmost 1 and plus 1.
vector<int> countBits(int num) {
    vector<int> v(num + 1, 0);
    for (int n = 1; n <= num; ++n) {
        v[n] = v[n&(n-1)] + 1;
    }
    return v;
}

// Remove rightmost bit and plus 1 or 0.
vector<int> countBits(int num) {
    vector<int> v(num + 1, 0);
    for (int n = 1; n <= num; ++n) {
        v[n] = v[n>>1] + (n&1);
    }
    return v;
}
