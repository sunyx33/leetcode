class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        int i = 0;
        int j = nums.size() - 1;
        while (i < j) {
            while (nums[i] % 2 == 1 && i < nums.size() - 1) i ++;
            while (nums[j] % 2 == 0 && j > 0) j --;
            if (i < j) swap(nums[i], nums[j]);
        }
        return nums;
    }
};