/*
 * @lc app=leetcode.cn id=20 lang=cpp
 *
 * [20] 有效的括号
 */
#include <stack>

using namespace std;
// @lc code=start
class Solution {
public:
    bool isValid(string s) {
        if (s.size() % 2 != 0) return false; // 长度为奇数一定不符合要求
        stack<char> sta;
        for (int i = 0; i < s.size(); i++) {
            if(s[i] == '(') sta.push(')');
            else if(s[i] == '[') sta.push(']');
            else if(s[i] == '{') sta.push('}');
            else if (sta.empty() || sta.top() != s[i]) return false;
            else sta.pop();
        }
        return sta.empty();
    }
};
// @lc code=end

