int minimumDeleteSum(string s1, string s2) {
    int m = s1.size(), n = s2.size();
    vector<vector<int>> dp(2, vector<int>(n+1, 0));
    for (int j = 1; j <= n; ++j) dp[0][j] = dp[0][j-1] + s2[j-1];
    for (int i = 1; i <= m; ++i) {
        dp[1][0] = dp[0][0] + s1[i-1];
        for (int j = 1; j <= n; ++j)
            dp[1][j] = s1[i-1] == s2[j-1] ? dp[0][j-1] : min(s1[i-1] + dp[0][j], s2[j-1] + dp[1][j-1]);
        dp[0] = dp[1];
    }
    return dp[0][n];
}