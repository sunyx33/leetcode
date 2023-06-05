/*
 * @lc app=leetcode.cn id=49 lang=cpp
 *
 * [49] 字母异位词分组
 */

// @lc code=start
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        unordered_map<string, vector<string>> uMap;
        for(string s : strs) {
            string key = s;
            sort(key.begin(), key.end());
            uMap[key].push_back(s);
        }

        for(auto& it : uMap) {
            result.push_back(it.second);
        }
        return result;
    }
};
// @lc code=end

