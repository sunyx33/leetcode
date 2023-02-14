/*
 * @lc app=leetcode.cn id=541 lang=cpp
 *
 * [541] 反转字符串 II
 */

// @lc code=start
class Solution {
public:
    string reverseStr(string s, int k) {
        for (int i = 1; (i - 1) * k < s.size(); i = i + 2 ) {
            if ((i * k - 1) < s.size()) {
                reverse(s, (i - 1) * k, i * k - 1);
            } else {
                reverse(s, (i - 1) * k, s.size() - 1);
            }
        }

        return s;
    }

    void reverse(string& s, int start, int end){
        while(start < end){
            swap(s[start], s[end]);
            start ++;
            end --;
        }
    }
};
// @lc code=end

