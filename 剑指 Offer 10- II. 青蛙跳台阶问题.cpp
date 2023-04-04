class Solution {
public:
    int numWays(int n) {
        vector<int> dp(2);
        dp[0] = 1;
        dp[1] = 1;
        for(int i = 2; i <= n; i++) {
            int res = (dp[0] + dp[1]) %1000000007;
            dp[0] = dp[1];
            dp[1] = res;
        }
        return dp[1];
    }
};  