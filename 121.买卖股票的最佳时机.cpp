/*
 * @lc app=leetcode.cn id=121 lang=cpp
 *
 * [121] 买卖股票的最佳时机
 */
#include <vector>

using namespace std;
// @lc code=start
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // 只依赖上一行，滚动数组省空间
        vector<vector<int>> dp(2, vector<int>(2));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        for (int i = 1; i < prices.size(); i++){
            dp[1][0] = max(dp[0][0], -prices[i]);
            dp[1][1] = max(dp[0][1], dp[0][0] + prices[i]);
            dp[0][0] = dp[1][0];
            dp[0][1] = dp[1][1];
        }

        return max(dp[1][0], dp[1][1]);
    }
};
// @lc code=end

