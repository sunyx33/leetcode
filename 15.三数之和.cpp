/*
 * @lc app=leetcode.cn id=15 lang=cpp
 *
 * [15] 三数之和
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());

        for(int i = 0; i < nums.size(); i++){
            // 从小到大排序，第一个都大于0则不可能和为0
            if(nums[i] > 0){
                return result;
            }

            int left = i + 1;
            int right = nums.size() - 1;

            // 对i进行去重
            if(i > 0 && nums[i] == nums[i-1]){
                continue;
            } 

            // 进行left与right的移动
            while (right > left) { 
                if(nums[i] + nums[left] + nums[right] > 0){
                    right --;
                } else if (nums[i] + nums[left] + nums[right] < 0)
                {
                    left ++;
                } else {
                    result.push_back(vector<int>{nums[i], nums[left], nums[right]});
                    // 去重逻辑应该放在找到一个三元组之后，对b 和 c去重
                    while (right > left && nums[right] == nums[right - 1]) right--;
                    while (right > left && nums[left] == nums[left + 1]) left++;

                    // 找到答案时，双指针同时收缩
                    right--;
                    left++;
                }
                
            }
            
        }
        return result;
    }
};
// @lc code=end

