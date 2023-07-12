class Solution {
public:
    int minFlipsMonoIncr(string s) {
        vector<int> dp(2, 0);
        dp[0] = s[0] != '0';
        dp[1] = s[0] != '1';
        for(int i = 1; i < s.size(); i++) {
            dp[1] = min(dp[0], dp[1]) + (s[i] != '1');
            dp[0] = dp[0] + (s[i] != '0');
            
        }
        return min(dp[0], dp[1]);
    }
};