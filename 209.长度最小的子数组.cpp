/*
 * @lc app=leetcode.cn id=209 lang=cpp
 *
 * [209] 长度最小的子数组
 */

// @lc code=start
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int result = __INT32_MAX__;
        int start = 0;
        int sum = 0;
        int sublenth = 0;
        for (int end = 0; end < nums.size(); end++) {
            sum += nums[end];
            while(sum >= target) {
                sublenth =  end - start + 1;
                result = result < sublenth ? result : sublenth;
                sum -= nums[start++];
            }
        }
        return result == __INT32_MAX__ ? 0 : result;
    }
};
// @lc code=end

