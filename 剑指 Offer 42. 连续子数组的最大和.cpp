class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int dp;
        dp = nums[0];
        int result = dp;
        for (int i = 1; i < nums.size(); i++) {
            dp = max(nums[i], dp + nums[i]);
            if(result < dp) result = dp;
        }
        return result;
    }
};