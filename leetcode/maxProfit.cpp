int maxProfit(vector<int>& prices) {        
    int minPrice = numeric_limits<int>::max(), maxPro = 0, profit;
    for (int p : prices) {
        profit = p - minPrice;
        if (profit < 0) minPrice = p;
        else if (profit > maxPro) maxPro = profit;
    }        
    return maxPro;
}
