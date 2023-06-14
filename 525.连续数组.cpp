/*
 * @lc app=leetcode.cn id=525 lang=cpp
 *
 * [525] 连续数组
 */
#include <vector>
#include <unordered_map>
using namespace std;
// @lc code=start
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int result = 0;
        int sum = 0;
        unordered_map<int, int> uMap;
        uMap[0] = -1;
        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] == 0) sum += -1;
            else sum += 1;
            if(uMap.find(sum) != uMap.end()) {
                result = max(result, i - uMap.find(sum)->second);
                continue;
            }
            uMap[sum] = i;
        }
        return result;
    }
};
// @lc code=end

