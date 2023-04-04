class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() <= 1) return 0;
        vector<vector<int>> dp(2, vector<int>(2));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        for (int i = 1; i < prices.size(); i++){
            dp[1][0] = max(dp[0][0], -prices[i]);
            dp[1][1] = max(dp[0][1], dp[0][0] + prices[i]);
            dp[0][0] = dp[1][0];
            dp[0][1] = dp[1][1];
        }

        return dp[1][1];
    }
};