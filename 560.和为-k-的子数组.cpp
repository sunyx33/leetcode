/*
 * @lc app=leetcode.cn id=560 lang=cpp
 *
 * [560] 和为 K 的子数组
 */

// @lc code=start
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> uMap;
        uMap[0] = 1;
        int sum = 0;
        int result = 0;
        for(int n : nums) {
            sum += n;
            if(uMap.find(sum - k) != uMap.end()) {
                result += uMap[sum - k];
            }
            uMap[sum] ++;
        }
        return result;
    }
};
// class Solution {
// public:
//     int subarraySum(vector<int> &nums, int k) {
//         int sum = 0, res = 0;
//         unordered_map<int, int> cul;
//         cul[0] = 1;
//         for (auto &m : nums) {
//             sum += m;
//             res += cul[sum - k];
//             ++cul[sum];
//         }
//         return res;
//     }
// };
// @lc code=end

