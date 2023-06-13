/*
 * @lc app=leetcode.cn id=76 lang=cpp
 *
 * [76] 最小覆盖子串
 */
#include <set>
using namespace std;
// @lc code=start
class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> need(128,0);
        int count = 0;  
        for(char c : t)
        {
            need[c]++;
        }
        count = t.length();
        int l=0, r=0, start=0, size = INT_MAX;
        while(r<s.length())
        {
            char c = s[r];
            if(need[c]>0)
                count--;
            need[c]--;  //先把右边的字符加入窗口
            if(count==0)    //窗口中已经包含所需的全部字符
            {
                while(l<r && need[s[l]]<0) //缩减窗口
                {
                    need[s[l++]]++;
                }   //此时窗口符合要求
                if(r-l+1 < size)    //更新答案
                {
                    size = r-l+1;
                    start = l;
                }
                need[s[l]]++;   //左边界右移之前需要释放need[s[l]]
                l++;
                count++;
            }
            r++;
        }
        return size==INT_MAX ? "" : s.substr(start, size);
    }
};
// @lc code=end

