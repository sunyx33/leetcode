/*
 * @lc app=leetcode.cn id=377 lang=cpp
 *
 * [377] 组合总和 Ⅳ
 */
#include <vector>

using namespace std;
// @lc code=start
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<int> dp(target + 1, 0);
        dp[0] = 1;
        for (int j = 0; j < dp.size(); j++){
            for (int i = 0; i < nums.size(); i++) {
                // C++测试用例有两个数相加超过int的数据，所以需要在if里加上dp[i] < INT_MAX - dp[i - num]。
                if (j - nums[i] >= 0 && dp[j] < __INT_MAX__ - dp[j - nums[i]]) { 
                    dp[j] += dp[j - nums[i]];
                }
            }  
        }
        
        return dp[target];        
    }
};
// @lc code=end

