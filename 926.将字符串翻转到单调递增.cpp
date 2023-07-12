/*
 * @lc app=leetcode.cn id=926 lang=cpp
 *
 * [926] 将字符串翻转到单调递增
 */

// @lc code=start
class Solution {
public:
    int minFlipsMonoIncr(string s) {
        vector<int> dp(2, 0);
        dp[0] = s[0] != '0';
        dp[1] = s[0] != '1';
        for(int i = 1; i < s.size(); i++) {
            dp[1] = min(dp[0], dp[1]) + (s[i] != '1'); // 不要忘记加括号
            dp[0] = dp[0] + (s[i] != '0');
        }
        return min(dp[0], dp[1]);
    }
};// @lc code=end

