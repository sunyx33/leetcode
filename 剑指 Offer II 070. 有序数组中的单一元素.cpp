class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        // 如果mid是偶数且与下一个数不同：目标在mid之前（包括mid）；否则在mid之后
        // 如果mid是奇数且与上一个数不同：目标在mid之前（不包括mid，目标索引不可能是奇数）；否则在mid之后
        int left = 0;
        int right = nums.size() - 1;
        while(right > left) {
            int mid = (left + right) / 2;
            if(mid % 2 == 0 && nums[mid] != nums[mid + 1]) right = mid;
            else if(mid % 2 == 0 && nums[mid] == nums[mid + 1]) left = mid + 1;
            else if(mid % 2 == 1 && nums[mid] != nums[mid - 1]) right = mid - 1;
            else left = mid + 1;
        }
        return nums[left];
    }
};