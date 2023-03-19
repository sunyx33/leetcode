/*
 * @lc app=leetcode.cn id=674 lang=cpp
 *
 * [674] 最长连续递增序列
 */
#include <vector>

using namespace std;
// @lc code=start
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        vector<int> dp(nums.size(), 1);
        int result = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > nums[i - 1]) dp[i]  = dp[i - 1] + 1;
            result = max(result, dp[i]);
        }
        return result;
    }
};
// @lc code=end
int main() {
    vector<int> nums = {1,3,5,4,7};
    Solution sol;
    sol.findLengthOfLCIS(nums);
    return 0;
}

