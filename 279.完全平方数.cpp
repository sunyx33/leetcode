/*
 * @lc app=leetcode.cn id=279 lang=cpp
 *
 * [279] 完全平方数
 */
#include <vector>

using namespace std;
// @lc code=start
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, __INT_MAX__);
        dp[0] = 0;
        for (int i = 1; i * i <= n; i++) {
            for (int j = i * i; j <= n; j++) {
                dp[j] = min(dp[j - i * i] + 1, dp[j]);
            }
        }
        return dp[n];
    }
};
// @lc code=end

