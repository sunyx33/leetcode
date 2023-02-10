#include <vector>
using namespace std;

/*
 * @lc app=leetcode.cn id=344 lang=cpp
 *
 * [344] 反转字符串
 */

// @lc code=start
class Solution {
public:
    void reverseString(vector<char>& s) {
        int left = 0;
        int right = s.size() - 1;
        while(right > left){
            swap(s[left], s[right]);
            left ++;
            right --;
        }
    }

    void swap(char& a, char& b){
        char temp = a;
        a = b;
        b = temp;
    }
};
// @lc code=end

