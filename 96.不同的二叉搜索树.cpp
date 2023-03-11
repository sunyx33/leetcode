/*
 * @lc app=leetcode.cn id=96 lang=cpp
 *
 * [96] 不同的二叉搜索树
 */
#include <vector>

using namespace std;
// @lc code=start
class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n + 1);
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= i / 2; j++) { // 左右对称，算一半即可
                dp[i] += dp[j - 1] * dp[i - j];
            }
            if(i % 2 == 0) dp[i] = dp[i] * 2;
            else dp[i] = dp[i] * 2 + dp[i / 2]  * dp[i / 2]; // 中位数做根节点
        }
        return dp[n];
    }
};
// @lc code=end

