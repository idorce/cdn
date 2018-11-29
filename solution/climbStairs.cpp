int climbStairs(int n) {
    int dp__ = 0, dp_ = 1, dp;
    while (n > 0 && --n) {
        dp = dp__ + dp_;
        dp__ = dp_;
        dp_ = dp;
    }
    return dp__ + dp_;
}
