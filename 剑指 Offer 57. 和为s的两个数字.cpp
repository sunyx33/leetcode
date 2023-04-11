class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            int sum = nums[left] + nums[right];
            if (sum == target) {
                return {nums[left], nums[right]};
            } 
            else if (sum > target) right --;
            else left ++; 
        }
        return {};
    }
};