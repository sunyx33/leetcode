/*
 * @lc app=leetcode.cn id=137 lang=cpp
 *
 * [137] 只出现一次的数字 II
 */

// @lc code=start
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int a = 0, b = 0;
        for (int num: nums) {
            tie(a, b) = pair{(~a & b & num) | (a & ~b & ~num), ~a & (b ^ num)};
        }
        return b;
    }
};
// @lc code=end

