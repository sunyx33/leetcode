/*
 * @lc app=leetcode.cn id=1047 lang=cpp
 *
 * [1047] 删除字符串中的所有相邻重复项
 */
#include <stack>
#include <deque>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    string removeDuplicates(string s) {
        deque<char> que;
        for (int i = 0; i < s.size(); i++) {
            if (que.empty() || que.back() != s[i]) {
                que.push_back(s[i]);
            } else {
                que.pop_back();
            }
        }

        string result;
        while (!que.empty()) {
            result += que.front();
            que.pop_front();
        }

        return result;
    }
};
// @lc code=end

