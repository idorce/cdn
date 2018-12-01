class NumArray {
public:
    vector<int> prefixSum{0};
    
    NumArray(vector<int> nums) {
        for (int n : nums) {
            prefixSum.push_back(prefixSum.back() + n);
        }
    }
    
    int sumRange(int i, int j) {
        return prefixSum[j + 1] - prefixSum[i];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * int param_1 = obj.sumRange(i,j);
 */
