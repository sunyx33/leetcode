/*
 * @lc app=leetcode.cn id=11 lang=cpp
 *
 * [11] 盛最多水的容器
 */

// @lc code=start
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        int result = 0;
        while(right > left) {
            int ans = (right - left) * min(height[left], height[right]);
            if(ans > result) result = ans;
            if(height[left] < height[right]) left ++;
            else right --;
        }
        return result;
    }
}; 
// @lc code=end

