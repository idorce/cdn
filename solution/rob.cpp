int rob(vector<int>& nums) {
    int dp__ = 0, dp_ = 0, dp = 0;
    for (int n : nums) {
        dp = max(dp_, dp__ + n);
        dp__ = dp_;
        dp_ = dp;
    }
    return dp;
}