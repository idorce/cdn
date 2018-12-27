// DP
int maxSubArray(vector<int> &nums) {
    int maxSum = nums[0], maxCon = nums[0];
    for (auto n = nums.begin() + 1; n != nums.end(); ++n) {
        maxCon = max(maxCon, 0) + *n;
        maxSum = max(maxSum, maxCon);
    }
    return maxSum;
}

// DC
auto dc(vector<int> &nums, int i, int j) {
     if (i == j - 1) return make_tuple(nums[i], nums[i], nums[i], nums[i]);
     
     // a: maxPrefixSum, m: maxAnySum, b: maxSuffixSum, s: allSum.
     int mid = (i + j) / 2, a, m, b, s, a1, m1, b1, s1, a2, m2, b2, s2;
     
     tie(a1, m1, b1, s1) = dc(nums, i, mid);
     tie(a2, m2, b2, s2) = dc(nums, mid, j);
     
     a = max(a1, s1 + a2);
     b = max(b2, s2 + b1);
     m = max(m1, m2);
     m = max(m, b1 + a2);
     s = s1 + s2;
        
    return make_tuple(a, m, b, s);
}

int maxSubArray(vector<int> &nums) {
    return get<1>(dc(nums, 0, nums.size()));
}
