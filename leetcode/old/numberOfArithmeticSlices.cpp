int numberOfArithmeticSlices(vector<int>& A) {
    int s = 0, dp = 0;
    for (int i = 2; i < A.size(); ++i){
        if (A[i] + A[i-2] == 2 * A[i-1]) {
            dp += 1;
            s += dp;
        }
        else dp = 0;
    }
    return s;
}
