/*
 * @lc app=leetcode.cn id=10 lang=cpp
 *
 * [10] 正则表达式匹配
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    bool isMatch(string s, string p) {
        // dp[i][j] 表示s[0, i - 1]与p[0, j - 1]是否可以匹配
        vector<vector<bool>> dp(s.size() + 1, vector<bool>(p.size() + 1, false));

        // 初始化：
        // dp[0][0]代表s与p均为空，可匹配
        dp[0][0] = true;
        // dp[i][0]代表s不空，p空，不匹配（初值为false，不用赋值）
        // dp[0][j]代表s空，p不空，由于*可匹配0个字符，所以可能匹配
        for(int j = 1; j <= p.size(); j++) {
            if(p[j - 1] == '*') { // 这里j其实一定大于1，因为只有一个*的匹配串是不合法的
                dp[0][j] = dp[0][j - 2];
            }
        }

        // 填格子
        for(int i = 1; i <= s.size(); i++) {
            for(int j = 1; j <= p.size(); j++) {
                if(s[i - 1] == p[j - 1] || p[j - 1] == '.') { // 如果末尾可以匹配上
                    dp[i][j] = dp[i - 1][j - 1];
                } else if(p[j - 1] == '*') { // 模式串末尾是*
                    if(s[i - 1] == p[j - 2] || p[j - 2] == '.') {
                        dp[i][j] = dp[i][j - 2]  // *匹配0次的情况
                                || dp[i - 1][j]; // *匹配1次以上的情况
                    } else { // 模式串*前一个字符与s串末尾不匹配
                        dp[i][j] = dp[i][j - 2]; // *只能匹配0次
                    }
                }
            }
        }
        return dp[s.size()][p.size()];
    }
};
// @lc code=end

