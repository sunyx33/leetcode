/*
 * @lc app=leetcode.cn id=123 lang=cpp
 *
 * [123] 买卖股票的最佳时机 III
 */
#include <vector>

using namespace std;
// @lc code=start
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(2, vector<int>(4));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        dp[0][2] = -prices[0];
        dp[0][3] = 0;
        for (int i = 1; i < prices.size(); i++) {
            dp[1][0] = max(0 - prices[i], dp[0][0]);
            dp[1][1] = max(dp[0][0] + prices[i], dp[0][1]);  
            dp[1][2] = max(dp[0][1] - prices[i], dp[0][2]);
            dp[1][3] = max(dp[0][2] + prices[i], dp[0][3]);
            dp[0] = dp[1];
        }
        return max(max(dp[1][0], dp[1][1]), max(dp[1][2], dp[1][3]));
        
    }
};
// @lc code=end

