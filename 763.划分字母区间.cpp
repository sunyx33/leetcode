/*
 * @lc app=leetcode.cn id=763 lang=cpp
 *
 * [763] 划分字母区间
 */
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> partitionLabels(string s) {
        int hash[26] = {0}; // i为字符，hash[i]为字符出现的最后位置
        for (int i = 0 ; i < s.size(); i++) { // 统计每一个字符最后出现的位置
            hash[s[i] - 'a'] = i;
        }
        vector<int> result;
        int left = 0;
        int right = 0;
        for (int i = 0; i < s.size(); i++) {
            right = max(right, hash[s[i] - 'a']); // 已经遍历到字符出现的最远边界
            if (i == right) {
                result.push_back(right - left + 1);
                left = i + 1;
            }
        }
        return result;
    }
};
// @lc code=end

