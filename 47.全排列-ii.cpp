/*
 * @lc app=leetcode.cn id=47 lang=cpp
 *
 * [47] 全排列 II
 */
#include <vector>

using namespace std;
// @lc code=start
class Solution {
private:
    vector<int> path;
    vector<vector<int>> result;

    void backtracking (vector<int>& nums, vector<bool>& used) {
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }
        int usedFor[20] = {0};
        for (int i = 0; i < nums.size(); i++) {
            if (used[i] == true || usedFor[nums[i] + 10] == 1) continue;
            path.push_back(nums[i]);
            usedFor[nums[i] + 10] = 1;
            used[i] = true;
            backtracking(nums, used);
            used[i] = false;
            path.pop_back();
        }

    }  
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<bool> used(nums.size(), false);
        backtracking(nums, used);
        return result;
    }
};
// @lc code=end

