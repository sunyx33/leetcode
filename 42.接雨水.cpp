/*
 * @lc app=leetcode.cn id=42 lang=cpp
 *
 * [42] 接雨水
 */
#include <vector>
#include <stack>
using namespace std;
// @lc code=start
class Solution {
public:
    int trap(vector<int>& height) {
        stack<int> st;
        int result = 0;
        st.push(0);
        for (int i = 1; i < height.size(); i++) {
            if (height[i] < height[st.top()]) {
                st.push(i);
            } else if (height[i] == height[st.top()]){
                st.pop();
                st.push(i);
            } else {
                while (!st.empty() && height[i] > height[st.top()]) {
                    int mid = st.top();
                    st.pop();
                    if(!st.empty()) {
                        int h = min(height[i], height[st.top()]) - height[mid];
                        int w = i - st.top() - 1;
                        result += h * w;
                    }
                }
                st.push(i);
            }
        }
        return result;
    }
};
// @lc code=end

