class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        // 二分查找区间规范很重要：左闭右开
        int left = 0;
        int right = nums.size();
        while(right > left) {
            int mid = (left + right) / 2;
            if(nums[mid] > target) right = mid;
            else if(nums[mid] < target) left = mid + 1;
            else return mid;
        }
        return left;
    }
};