/*
 * @lc app=leetcode.cn id=220 lang=cpp
 *
 * [220] 存在重复元素 III
 */

// @lc code=start
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        set<int> window;
        for(int i = 0; i < nums.size(); i++) {
            auto iter  = window.lower_bound(nums[i] - t);
            if(iter != window.end() && *iter <= nums[i] + t) return true;
            window.emplace(nums[i]);
            if(i >= k) {
                window.erase(nums[i - k]);
            }
        }
        return false;
    }
};
// @lc code=end

