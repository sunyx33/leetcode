/*
 * @lc app=leetcode.cn id=338 lang=cpp
 *
 * [338] 比特位计数
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int log_floor(int i) {
        int n = 0;
        while(pow(2, n) <= i) n++;
        return n - 1;
    }
    vector<int> countBits(int n) {
        vector<int> result(n + 1, 0);
        for(int i = 1; i <= n; i ++) {
            int n = log_floor(i);
            result[i] = 1 + result[i - pow(2, n)];
        }
        return result;
    }
};
// @lc code=end

