/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 */

// @lc code=start
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> res;
        for(int i = 0; i < nums.size(); i++){
            auto iter = res.find(target - nums[i]);
            if(iter != res.end()){
                return {iter->second, i};
            }
            res.insert(pair<int, int>(nums[i], i));
        }
        return {};
    }
};
// @lc code=end

