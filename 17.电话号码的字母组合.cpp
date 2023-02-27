/*
 * @lc app=leetcode.cn id=17 lang=cpp
 *
 * [17] 电话号码的字母组合
 */
#include <string>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    string path;
    vector<string> result;
    const vector<string> alph = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    void backtracking(string digits, int curIndex) {
        if (path.length() == digits.length()) {
            result.push_back(path);
            return;
        }
        string curAlph = alph[(int)digits[curIndex] - 50];
        for (int i = 0; i < curAlph.length(); i ++) {
            path.push_back(curAlph[i]);
            backtracking(digits, curIndex + 1); // idx + 1不会超出边界，因为当path与digits一样长时就结束递归了
            path.pop_back();
        }
    }

    vector<string> letterCombinations(string digits) {
        if (digits.length() > 0) {
            backtracking (digits, 0);
        }
        return result;
    }
};
// @lc code=end

int main(){
    Solution sol;
    string digits = "23"; 
    // int a = (int)digits[1] - 48;
    sol.letterCombinations(digits);
    return 0;
}

