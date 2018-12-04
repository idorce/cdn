int minFallingPathSum(vector<vector<int>>& A) {
    int n = A.size();
    for (int i = 1; i < n; ++i)
        for (int j = 0; j < n; ++j)
            A[i][j] += min({A[i-1][max(0,j-1)], A[i-1][j], A[i-1][min(j+1,n-1)]});
    return *min_element(A[n-1].begin(), A[n-1].end());
}
