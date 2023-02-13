/*
 * @lc app=leetcode.cn id=704 lang=cpp
 *
 * [704] 二分查找
 */

// @lc code=start
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int start = 0;
        int end = nums.size() - 1;
        while (end >= start) {
            int middle = start + (end - start) / 2;
            if (target > nums[middle]) {
                start = middle + 1;
            } else if (target < nums[middle]) {
                end = middle - 1;
            } else {
                return middle;
            }
        }

        return -1;
    }
};
// @lc code=end

