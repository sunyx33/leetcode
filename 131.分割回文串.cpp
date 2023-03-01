/*
 * @lc app=leetcode.cn id=131 lang=cpp
 *
 * [131] 分割回文串
 */
#include <string>
#include <vector>

using namespace std;
// @lc code=start
class Solution {
private:
    vector<string> path;
    vector<vector<string>> result; 
    bool isPalindrome (const string& s, int start, int end) {
        for (int i = start, j = end; i < j; i++, j--) {
            if (s[i] != s[j]) {
                return false;
            }
        }
        return true;
    }

    void backtracking (const string& s, int startIndex) {
        // 若启示位置大于s的大小，说明找到一组分割方案
        if (startIndex >= s.size()) {
            result.push_back(path);
            return;
        }

        for (int i = startIndex; i < s.size(); i++) {
            if (isPalindrome(s, startIndex, i)) {
                // [startIndex, i]
                string str = s.substr(startIndex, i - startIndex + 1);
                path .push_back(str);
            } else {
                continue;
            }
            backtracking(s, i + 1);
            path.pop_back();
        }
    }

public:
    vector<vector<string>> partition(string s) {
        backtracking(s, 0);
        return result;
    }
};
// @lc code=end

