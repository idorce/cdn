# DP

## 5. Longest Palindromic Substring

```cpp
// dp[i, j] == 1：s[i:j+1]是回文。
// dp[i, j] = dp[i + 1, j - 1] && s[i] == s[j]
// dp[i, i + 1] = dp[i, i - 1] = 1
class Solution {
public:
    string longestPalindrome(string s) {
        int s_len = s.size(), tmp_len, max_len = 1, start_index = 0;
        vector<int> dp(s_len, 1);
        for (int i = s_len - 2; i >= 0; --i) {
            for (int j = s_len - 1; j > i; --j) {
                dp[j] = dp[j - 1] && s[i] == s[j];
                // Check for longest.
                if (dp[j]) {
                    tmp_len = j - i + 1;
                    if (tmp_len > max_len){
                        max_len = tmp_len;
                        start_index = i;
                    }
                }
            }
        }
        return s.substr(start_index, max_len);
    }
};
```