int minCostClimbingStairs(vector<int>& cost) {
    int dp__ = 0, dp_ = 0, dp;
    for (int c : cost) {
        dp = min(dp_, dp__) + c;
        dp__ = dp_;
        dp_ = dp;
    }
    return min(dp_, dp__);
}
