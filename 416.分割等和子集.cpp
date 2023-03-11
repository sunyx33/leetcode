/*
 * @lc app=leetcode.cn id=416 lang=cpp
 *
 * [416] 分割等和子集
 */
#include <vector>
#include <algorithm>

using namespace std;
// @lc code=start
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }

        if (sum % 2 == 0) sum /= 2;
        else return false;

        vector<int> dp(sum + 1);

        for (int i = 0; i < nums.size(); i++){
            for (int j = sum; nums[i] <= j; j--) {
                dp[j] = max(dp[j], dp[j-nums[i]]+nums[i]);
            }
        }

        return dp[sum] == sum;
    }
};
// @lc code=end

