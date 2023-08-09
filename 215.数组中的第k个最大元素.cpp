/*
 * @lc app=leetcode.cn id=215 lang=cpp
 *
 * [215] 数组中的第K个最大元素
 */
#include <queue>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int partition(vector<int>& nums, int l, int r) {
        int location = l;
        int pivot = r;
        for(int i = l; i < r; i++) {
            if(nums[i] < nums[pivot]) swap(nums[i], nums[location++]);
        }
        swap(nums[location], nums[pivot]);
        return location;
    }

    int randomPartition(vector<int>& nums, int l, int r) {
        int i = rand() % (r - l + 1) + l;
        swap(nums[i], nums[r]);
        return partition(nums, l, r);
    }

    int quickSort(vector<int>& nums, int l, int r, int idx) {
        if(r < l) return 0;
        int pivot = randomPartition(nums, l, r);
        if(pivot == idx) return nums[pivot];
        else return pivot < idx ? quickSort(nums, pivot + 1, r, idx) : quickSort(nums, l, pivot - 1, idx);
    }

    int findKthLargest(vector<int>& nums, int k) {
        return quickSort(nums, 0, nums.size() - 1, nums.size() - k);
    }
};
// @lc code=end

