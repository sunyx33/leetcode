/*
 * @lc app=leetcode.cn id=69 lang=cpp
 *
 * [69] x 的平方根 
 */

// @lc code=start
class Solution {
public:
    int mySqrt(int x) {
        long left = 0;
        long right = x;
        while(right > left) {
            long mid = (left + right) / 2;
            if(mid * mid == x || ( (mid * mid) < x && (mid + 1) * (mid + 1) > x) ) return mid;
            else if((mid * mid) > x) right = mid - 1;
            else left = mid + 1;
        }
        return left;
    }
};
// @lc code=end

