/*
 * @lc app=leetcode.cn id=875 lang=cpp
 *
 * [875] 爱吃香蕉的珂珂
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int left = 1;
        int right = 0;
        for(int n : piles) {
            if(n > right) right = n;
        }
        while(right > left) {
            int mid = (left + right) / 2;
            if(check(piles, mid, h)) right = mid;
            else left = mid + 1;
        }
        return left;
    }

    bool check(vector<int>& piles, int k, int h) {
        int time = 0;
        for(int n : piles) {
            time += ceil(n * 1.0 / k);
        }
        return time <= h;
    }

};
// @lc code=end

