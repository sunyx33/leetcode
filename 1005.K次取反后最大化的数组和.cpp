/*
 * @lc app=leetcode.cn id=1005 lang=cpp
 *
 * [1005] K 次取反后最大化的数组和
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
private:
    int sum(vector<int>& nums) {
        int res = 0;
        for (int i = 0; i < nums.size(); i++) {
           res +=nums[i];
        }
        return res;
        
    }
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        int absMin = INT_MAX;
        int absMinIdx = 0;
        sort(nums.begin(), nums.end());
        int i = 0;
        while (k) {
            if (abs(nums[i]) < absMin) {
                absMin = abs(nums[i]);
                absMinIdx = i;
            }
            if (nums[i] < 0) {
                nums[i] = - nums[i];
                k--;
                if (i < nums.size() - 1) i++;
            } else {
                while (k) {
                    nums[absMinIdx] = - nums[absMinIdx];
                    k--;
                    if (i < nums.size() - 1) i++;
                }
            }
        }

        return sum(nums);
        
    }
};
// @lc code=end

int main() {
    Solution sol;
    vector<int> nums = {-4, -2, -3};
    sol.largestSumAfterKNegations(nums, 4);
    return 0;
}