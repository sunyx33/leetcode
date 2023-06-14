/*
 * @lc app=leetcode.cn id=713 lang=cpp
 *
 * [713] 乘积小于 K 的子数组
 */

// @lc code=start
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int left = 0;
        int mul = 1;
        int result = 0;
        for(int right = 0; right < nums.size(); right ++) {
            mul *= nums[right];
            while(mul >= k) {
                mul /= nums[left];
                left ++;
                if(left > right) break;
            }
            if(mul < k) result += right - left + 1;
        }
        return result;
    }
};
// @lc code=end

