/*
 * @lc app=leetcode.cn id=202 lang=cpp
 *
 * [202] 快乐数
 */

// @lc code=start
class Solution {
public:
    int getSum(int n){
        int sum = 0;
        while (n) {
            sum += (n % 10 ) * (n % 10);
            n /= 10;
        }

        return sum;
    }
    bool isHappy(int n) {
        unordered_set<int> res;
        while (1) {
            n = getSum(n);
            if (n == 1) {
                return true;
            }

            if (res.find(n) != res.end()){
                return false;
            } else {
                res.insert(n);
            }
        }        
    }
};
// @lc code=end

