/*
 * @lc app=leetcode.cn id=29 lang=cpp
 *
 * [29] 两数相除
 */

// @lc code=start
class Solution {
public:
    int divide(int a, int b) {
        if(a == 0) return 0;
        if(b == 1) return a;
        if(b == -1) {
            if(a > INT_MIN) return -a;
            else return INT_MAX;
        }
        int sign = 1;
        long aL = a;
        long bL = b;
        if((aL > 0 && bL < 0) || (aL < 0 && bL > 0)) sign = -1;
        if(aL < 0) aL = -aL;
        if(bL < 0) bL = -bL;
        
        int res = fastDiv(aL, bL);
        return sign == 1 ? res : -res; 
    }

    int fastDiv(long a, long b) {
        if(a < b) return 0;
        int cnt = 1;
        long bCopy = b;
        while(a > bCopy + bCopy) {
            cnt += cnt;
            bCopy += bCopy;
        }
        return cnt + fastDiv(a - bCopy, b);
    }
};
// @lc code=end

