int countSubstrings(string s) {
    int l = s.size(), n = l;
    vector<int> v(l, true);
    for (int i = l - 2; i >= 0; --i)
        for (int j = l - 1; j > i; --j) {
            v[j] = (s[i] == s[j]) && v[j-1];
            n += (int)(v[j]);
        }
    return n;
}
