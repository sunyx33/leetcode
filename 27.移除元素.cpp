#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/*
 * @lc app=leetcode.cn id=27 lang=cpp
 *
 * [27] 移除元素
 */
// @lc code=start
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int res = 0;
        if(nums.size() == 0) {
            return res;
        }
        int right = nums.size() - 1;
        int left = 0;
        sort(nums.begin(), nums.end());
        while (1) {
            if (nums[left] < val) {
                if (nums[right] > val) {
                    left ++;
                }  else if (nums[right] == val) {
                    right --;
                } else {
                    res = right + 1;
                    break;
                }
            } else if (nums[left] == val) {
                if (nums[right] > val) {
                    nums[left] = nums[right];
                    left ++;
                    right --;
                } else if (nums[right] == val) {
                    res = left;
                    break;
                } else {
                    break;
                }                
            } else {
                if (nums[right] > val) {
                    res = right + 1;
                    break;
                } else {
                    break;
                }
            }
        }

        return res;
    }

};
// @lc code=end

int main(int argc,char* argv[]){
    Solution s;
    vector<int> test = {0,1,2,2,3,0,4,2};
    int target = 2;
    int res = s.removeElement(test, target);

    return 0;
}

