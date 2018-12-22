// even number of piles
bool stoneGame(vector<int>& piles) {
    return true;
}

// DP
bool stoneGame(vector<int>& p) {
    vector<int> dp = p;
    for (int i = p.size() - 2; i >= 0; --i)
        for (int j = i + 1; j <= p.size() - 1; ++j)
            dp[j] = max(p[i] - dp[j], p[j] - dp[j-1]);
    return dp[p.size() - 1] > 0;
}
