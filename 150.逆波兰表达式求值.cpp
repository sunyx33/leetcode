/*
 * @lc app=leetcode.cn id=150 lang=cpp
 *
 * [150] 逆波兰表达式求值
 */
#include <vector>
#include <stack>
#include <string>

using namespace std;
// @lc code=start
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> sta;
        for (int i = 0; i < tokens.size(); i++) {
            if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/") {
                int num1 = sta.top();
                sta.pop();
                int num2 = sta.top();
                sta.pop();
                if (tokens[i] == "+") sta.push(num2 + num1);
                if (tokens[i] == "-") sta.push(num2 - num1);
                if (tokens[i] == "*") sta.push(num2 * num1);
                if (tokens[i] == "/") sta.push(num2 / num1);
            } else {
                sta.push(stoll(tokens[i]));
            }

        }
        return sta.top();
    }
};
// @lc code=end

