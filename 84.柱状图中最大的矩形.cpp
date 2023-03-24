/*
 * @lc app=leetcode.cn id=84 lang=cpp
 *
 * [84] 柱状图中最大的矩形
 */
#include <stack>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int result = 0;
        stack<int> st;
        heights.insert(heights.begin(), 0);
        heights.push_back(0);
        st.push(0);

        for (int i = 1; i < heights.size(); i++) {
            if (heights[i] > heights[st.top()]) {
                st.push(i);
            } else if (heights[i] == heights[st.top()]) {
                st.pop();
                st.push(i);
            } else {
                while (!st.empty() && heights[i] < heights[st.top()]) {
                    int mid = st.top();
                    st.pop();
                    if(!st.empty()) {
                        int left = st.top();
                        int right = i;
                        int w = right - left - 1;
                        int h = heights[mid];
                        result = max(result, w * h);
                    }
                }
                st.push(i);
            }
        }
        return result;
    }
};
// @lc code=end

