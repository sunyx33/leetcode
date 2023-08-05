/*
 * @lc app=leetcode.cn id=852 lang=cpp
 *
 * [852] 山脉数组的峰顶索引
 */

// @lc code=start
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int left = 0;
        int right = arr.size();
        while(right > left) {
            int mid = (left + right) / 2;
            if(arr[mid - 1] < arr[mid] && arr[mid + 1] < arr[mid]) return mid;
            else if(arr[mid - 1] > arr[mid]) right = mid;
            else left = mid + 1;
        }
        return -1;
    }
};
// @lc code=end

