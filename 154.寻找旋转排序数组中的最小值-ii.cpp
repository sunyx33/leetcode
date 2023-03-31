/*
 * @lc app=leetcode.cn id=154 lang=cpp
 *
 * [154] 寻找旋转排序数组中的最小值 II
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int findMin(vector<int>& nums) {
        int i = 0;
        int j = nums.size() - 1;
        while (i < j) {
            int m = (j + i) / 2;
            if (nums[m] < nums[j]) {
                j = m;
            } else if (nums[m] > nums[j]) {
                i = m + 1;
            } else j--;
        }
        return nums[i];
    }
};
// @lc code=end

