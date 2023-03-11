/*
 * @lc app=leetcode.cn id=494 lang=cpp
 *
 * [494] 目标和
 */
#include <vector>

using namespace std;
// @lc code=start
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }

        if(abs(target) > sum) return 0;
        if ((sum + target) % 2 == 1) return 0;
        int bagSize = (sum + target) / 2;

        vector<int> dp(bagSize + 1, 0);
        dp[0] = 1;

        for (int i = 0; i < nums.size(); i++) {
            for (int j = bagSize; j >= nums[i]; j--) {
                dp[j] += dp[j - nums[i]];
            }
        }

        return dp[bagSize];
        
    }
};
// @lc code=end

