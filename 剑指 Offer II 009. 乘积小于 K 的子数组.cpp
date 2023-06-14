class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int left = 0;
        int mul = 1;
        int result = 0;
        for(int right = 0; right < nums.size(); right ++) {
            mul *= nums[right];
            while(mul >= k) {
                mul /= nums[left ++];
                if(left > right) break;
            }
            if(mul < k) result += right - left + 1;
        }
        return result;
    }
};