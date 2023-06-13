/*
 * @lc app=leetcode.cn id=67 lang=cpp
 *
 * [67] 二进制求和
 */

// @lc code=start
class Solution {
public:
    int add(int a, int b, int& carry) {
        int result = a ^ b ^ carry;
        int cnt = (a == 1) + (b == 1) + (carry == 1);
        if(cnt >= 2) carry = 1;
        else carry = 0;
        return result;
    }

    string stack2str(stack<char>& sta) {
        string res = "";
        while(!sta.empty()) {
            res += sta.top();
            sta.pop();
        }
        return res;
    }

    string addBinary(string a, string b) {
        stack<char> result;
        if(b.size() > a.size()) swap(a, b);
        int carry = 0;
        int aPtr = a.size() - 1;
        int bPtr = b.size() - 1;
        while(aPtr >= 0 && bPtr >= 0) {
            result.push(add(a[aPtr] - '0', b[bPtr] - '0', carry) + '0');
            aPtr --;
            bPtr --;
        }
        while(aPtr >= 0 || carry) {
            if(aPtr >= 0) {
                result.push(add(a[aPtr] - '0', 0, carry) + '0');
                aPtr --;
            } else {
                carry = 0;
                result.push('1');
            }
        }

        return stack2str(result);
    }
};
// @lc code=end

