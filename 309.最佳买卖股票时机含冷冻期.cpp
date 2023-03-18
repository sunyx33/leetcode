/*
 * @lc app=leetcode.cn id=309 lang=cpp
 *
 * [309] 最佳买卖股票时机含冷冻期
 */

// @lc code=start
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(2, vector<int>(4));
        dp[0][0] = -prices[0];
        for (int i = 1; i < prices.size(); i++){
            dp[1][0] = max(dp[0][0], max(dp[0][3] - prices[i], dp[0][1] - prices[i])); // 前一天已持有、前一天冷冻期、前一天已卖出
            dp[1][1] = max(dp[0][1], dp[0][3]);
            dp[1][2] = dp[0][0] + prices[i];
            dp[1][3] = dp[0][2];
            dp[0] = dp[1];
        }

        int result = 0;
        for (int j = 0; j < 4; j++) {
            result = max(result, dp[1][j]);
        }

        return result;
    }
};
// @lc code=end

