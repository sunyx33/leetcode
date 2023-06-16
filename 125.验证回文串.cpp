/*
 * @lc app=leetcode.cn id=125 lang=cpp
 *
 * [125] 验证回文串
 */

// @lc code=start
class Solution {
public:
    bool isLetter(char& c) {
        if('A' <= c && 'Z' >= c) {
            c += 32;
            return true;
        } else if(('0' <= c && '9' >= c) || ('a' <= c && 'z' >= c)) return true;
        return false;
    }

    bool isPalindrome(string s) {
        int slow = 0;
        int fast = 0;
        for(; fast < s.size(); fast ++) {
            if(isLetter(s[fast])) {
                s[slow++] = s[fast];
            }
        }
        fast = slow - 1;
        slow = 0;
        while(slow < fast) {
            if(s[slow++] != s[fast--]) return false;
        }
        return true;
    }
};
// @lc code=end

