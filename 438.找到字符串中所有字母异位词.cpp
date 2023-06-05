/*
 * @lc app=leetcode.cn id=438 lang=cpp
 *
 * [438] 找到字符串中所有字母异位词
 */
#include <unordered_map>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> mapS(26, 0), mapP(26, 0);
        vector<int> result;
        if(s.size() < p.size()) return result;
        for(char c : p) {
            mapP[c - 'a'] ++;
        }

        for(int i = 0; i < s.size(); i++) {
            mapS[s[i] - 'a'] ++;
            if(i >= p.size() - 1) {
                if(mapP == mapS) result.push_back(i - p.size() + 1);
                mapS[s[i - p.size() + 1] - 'a'] --;
            }
        }
        return result;
    }
};
// @lc code=end

