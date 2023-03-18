/*
 * @lc app=leetcode.cn id=714 lang=cpp
 *
 * [714] 买卖股票的最佳时机含手续费
 */

// @lc code=start
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        vector<vector<int>> dp(2, vector<int>(2));
        dp[0][0] = -prices[0] - fee;
        for (int i = 1; i < prices.size(); i++){
            dp[1][0] = max(dp[0][0], dp[0][1] - prices[i] - fee);
            dp[1][1] = max(dp[0][1], dp[0][0] + prices[i]);
            dp[0] = dp[1];
        }

        return max(dp[1][0], dp[1][1]);
    }
};
// @lc code=end

