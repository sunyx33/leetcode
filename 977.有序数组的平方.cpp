#include <vector>
#include <iostream>

using namespace std;
/*
 * @lc app=leetcode.cn id=977 lang=cpp
 *
 * [977] 有序数组的平方
 */

// @lc code=start
// @lc code=end

int main(){
    Solution sol;
    vector<int> a = {-4, -1, 0, 3, 10};
    vector<int>& nums = a;
    nums = sol.sortedSquares(nums);
    for(int i = 0; i < nums.size(); i++) {
        cout << nums[i] << endl;
    }

    return 0;
}

