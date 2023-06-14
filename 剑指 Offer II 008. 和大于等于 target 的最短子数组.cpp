class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int sum = 0;
        int left = 0;
        int subLenth = 0;
        int result = INT_MAX;
        for(int right = 0; right < nums.size(); right ++) {
            sum += nums[right];
            while(sum >= target) {
                subLenth = right - left + 1;
                result = min(subLenth, result);
                sum -= nums[left ++];
            }
        }
        return result == __INT32_MAX__ ? 0 : result;
    }
};