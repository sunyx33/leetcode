/*
 * @lc app=leetcode.cn id=946 lang=cpp
 *
 * [946] 验证栈序列
 */

// @lc code=start
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> sta;
        int cur = 0;
        for(int num : pushed) {
            sta.push(num);
            while(cur < popped.size() && !sta.empty() && sta.top() == popped[cur]) {
                sta.pop();
                cur ++;
            }
        }
        return cur == popped.size();
    }
};
// @lc code=end

