int climbStairs(int n) {
    if (n <= 1) return 1;
    
    int dp__ = 0, dp_ = 1, dp;
    while (--n) {
        dp = dp__ + dp_;
        dp__ = dp_;
        dp_ = dp;
    }
    return dp__ + dp_;
}
