/*
 * @lc app=leetcode.cn id=516 lang=cpp
 *
 * [516] 最长回文子序列
 */
#include <vector>
#include <string>

using namespace std;
// @lc code=start
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        vector<vector<int>> dp(s.size(), vector<int>(s.size()));
        for(int i = 0; i < s.size(); i++) {
            dp[i][i] = 1;
        }
        for (int i = s.size() - 1; i >= 0; i--) {
            for (int j = 0; j < s.size(); j++) {
                if(j > i) {
                    if(s[i] == s[j]) dp[i][j] = dp[i + 1][j - 1] + 2;
                    else dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[0][s.size() - 1];
    }
};
// @lc code=end

