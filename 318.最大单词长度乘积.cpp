/*
 * @lc app=leetcode.cn id=318 lang=cpp
 *
 * [318] 最大单词长度乘积
 */

// @lc code=start
class Solution {
public:
    int maxProduct(vector<string>& words) {
        vector<int> hash(words.size(), 0);
        for(int i = 0; i < words.size(); i++) {
            for(char c : words[i]) {
                hash[i] |= 1 << (c - 'a');
            }
        }

        int maxResult = 0;
        for(int i = 0; i < words.size(); i++) {
            for(int j = i + 1; j < words.size(); j++) {
                if((hash[i] & hash[j]) == 0) {
                    int result = words[i].size() * words[j].size();
                    maxResult = max(result, maxResult);
                }
            }
        }
        return maxResult;
    }
};
// @lc code=end

