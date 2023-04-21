/*
 * @lc app=leetcode.cn id=8 lang=cpp
 *
 * [8] 字符串转换整数 (atoi)
 */

// @lc code=start
class Solution {
public:
    int myAtoi(string str) {
        long num = 0;
        int i = 0;
        bool isNeg = false;
        while(i < str.size()) {
            if(str[i] == ' ') {
                i ++;
            } else break;
        }
        if (str[i] == '-' || str[i] == '+') {
            isNeg = str[i] == '-';
            i ++;
        }

        while(i < str.size()) {
            if (str[i] < '0' || str[i] > '9') {
                break;
            } else {
                num = num * 10 + str[i] - '0';
                if(isNeg == false && num > INT_MAX) return INT_MAX;
                else if(isNeg == true && -num < INT_MIN) return INT_MIN;
                i++;
            }
        }
        return isNeg ? -num : num;

    }
};
// @lc code=end

