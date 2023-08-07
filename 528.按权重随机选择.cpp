/*
 * @lc app=leetcode.cn id=528 lang=cpp
 *
 * [528] 按权重随机选择
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> vec;
    Solution(vector<int>& w) {
        partial_sum(w.begin(), w.end(), back_inserter(vec));
    }
    
    int pickIndex() {
        return upper_bound(vec.begin(), vec.end(), rand() % vec.back()) - vec.begin();
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
// @lc code=end

