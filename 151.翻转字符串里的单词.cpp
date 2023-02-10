#include <string>
#include <iostream>

using namespace std;
/*
 * @lc app=leetcode.cn id=151 lang=cpp
 *
 * [151] 反转字符串中的单词
 */

// @lc code=start
class Solution {
public:
    string reverseWords(string s) {
        delEmpty(s);
        reverse(s, 0, s.size() - 1);
        for (int i = 0; i < s.size(); i++){
            int start = i;
            while(i < s.size() && s[i] != ' ') {
                i ++;
            }
            reverse(s, start, i - 1);
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

    void swap(char& a, char& b){
        char temp = a;
        a = b;
        b = temp;
    }

    void delEmpty(string& s){
        int slow = 0;
        for (int fast = 0; fast < s.size(); fast++) {
            if (s[fast] != ' ') {
                if (slow != 0) s[slow++] = ' ';
                while (fast < s.size() && s[fast] != ' ') { 
                    s[slow++] = s[fast++];
                }
            }
        }
        
        s.resize(slow);
    }
};
// @lc code=end


int main(){
    string s = "  string you ";
    Solution sol;
    s = sol.reverseWords(s);
    cout << s << endl;
    return 0;
}

