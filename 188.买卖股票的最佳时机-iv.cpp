/*
 * @lc app=leetcode.cn id=188 lang=cpp
 *
 * [188] 买卖股票的最佳时机 IV
 */

// @lc code=start
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        vector<vector<int>> dp(2, vector<int>(2 * k));
        for(int j = 0; j < 2 * k; j++) {
            if (j % 2 == 0) {
                dp[0][j] = -prices[0];
            } else dp[0][j] = 0;
        }
        for (int i = 1; i < prices.size(); i++) {
            for (int j = 0; j < 2 * k; j++){
                if (j == 0)          dp[1][j] = max(0 - prices[i]           , dp[0][j]);
                else if (j % 2 == 0) dp[1][j] = max(dp[0][j - 1] - prices[i], dp[0][j]);
                else                 dp[1][j] = max(dp[0][j - 1] + prices[i], dp[0][j]);
            }
            dp[0] = dp[1];
        }
        
        int result = 0;
        for (int j = 0; j < 2 * k; j++) {
            result = max(result, dp[1][j]);
        }
        return result;
    }
};
// @lc code=end

