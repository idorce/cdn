int maxProfit(vector<int>& prices, int fee) {
    long dp0 = 0, dp1 = numeric_limits<int>::min(), dp_0;
    for (int price : prices) {
        dp_0 = dp0;
        dp0 = max(dp0, dp1 + price - fee);
        dp1 = max(dp1, dp_0 - price);
    }
    return dp0;
}