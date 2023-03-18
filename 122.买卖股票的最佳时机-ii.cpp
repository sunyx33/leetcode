/*
 * @lc app=leetcode.cn id=122 lang=cpp
 *
 * [122] 买卖股票的最佳时机 II
 */

// @lc code=start
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // 贪心
        // int sum = 0;
        // for (int i = 0; i < prices.size() - 1; i++){
        //     if(prices[i + 1] - prices[i] > 0) {
        //         sum += prices[i + 1] - prices[i];
        //     }
        // }
        // return sum;
        
        // 动规
        vector<vector<int>> dp(2, vector<int>(2));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        for (int i = 1; i < prices.size(); i++){
            dp[1][0] = max(dp[0][0], dp[0][1]-prices[i]);
            dp[1][1] = max(dp[0][1], dp[0][0] + prices[i]);
            dp[0] = dp[1];
        }

        return max(dp[1][0], dp[1][1]);
    }
};
// @lc code=end

