int maxProfit(vector<int> &prices) {
    if (prices.size() <= 1) return 0;

    int minPrice = prices[0], maxPro = 0;

    for (auto p = prices.begin() + 1; p != prices.end(); ++p) {
        int profit = *p - minPrice;
        if (profit < 0) minPrice = *p;
        else if (profit > maxPro) maxPro = profit;
    }

    return maxPro;
}