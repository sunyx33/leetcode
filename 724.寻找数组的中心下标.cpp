/*
 * @lc app=leetcode.cn id=724 lang=cpp
 *
 * [724] 寻找数组的中心下标
 */

// @lc code=start
class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int rightSum = 0;
        for(int n : nums) rightSum += n;
        int leftSum = 0;
        for(int i = 0; i < nums.size(); i++){
            if(i > 0) leftSum += nums[i - 1];
            rightSum -= nums[i];
            if(leftSum == rightSum) return i;
        }
        return -1;
    }
};
// @lc code=end

