/*
 * @lc app=leetcode.cn id=128 lang=cpp
 *
 * [128] 最长连续序列
 */
#include <unordered_set>
using namespace std;
// @lc code=start
// class Solution {
// public:
//     int longestConsecutive(vector<int>& nums) {
//         if(nums.size() == 0) return 0;
//         sort(nums.begin(), nums.end());
//         int cnt = 1;
//         int result = 1;
//         for(int i = 0; i < nums.size(); i++) {
//             if(i == 0) continue;
//             if(nums[i] == nums[i - 1] + 1) {
//                 cnt ++;
//                 if(cnt > result) result = cnt;
//             } else if(nums[i] == nums[i - 1]) continue;
//             else cnt = 1;
//         }
//         return result;
//     }
// };
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        unordered_map<int, int> uMap;
        int cnt = 1;
        int result = 1;
        bool flag = false;
        for(int n : nums) {
            cnt = 1;
            if(uMap.find(n) != uMap.end()) continue;
            if(uMap.find(n - 1) != uMap.end()) {
                cnt += uMap[n - 1];
                if(uMap[n - 1] != 1) flag = true;
                uMap[n - uMap[n - 1]] = cnt;
                if(cnt > result) result = cnt;
            } 
            if(uMap.find(n + 1) != uMap.end()){
                cnt += uMap[n + 1];
                uMap[n + uMap[n + 1]] = cnt;
                if(flag) {
                    if(uMap.find(n - 1) != uMap.end()) uMap[n - uMap[n - 1]] = cnt;
                } else {
                    if(uMap.find(n - 1) != uMap.end()) uMap[n - uMap[n - 1] + 1] = cnt;
                }
                
                if(cnt > result) result = cnt;
            }
            uMap[n] = cnt;
            flag = false;
        }
        return result;
    }
};
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        // 使用 unorder_set 锚住 nums 中的元素，并去重
        unordered_set<int> sorted;
        for (int num : nums) {
            sorted.insert(num);
        }
        int maxLen = 0;
        for (int num : sorted) {
            if (!sorted.count(num - 1)) { // 剪掉非连续部分，从连续的第二个元素开始计数
                int len = 1;
                while (sorted.count(num + 1)) {
                    len++;
                    num++;
                }
                maxLen = max(maxLen, len);
            }
        }
        return maxLen;
    }
};
// @lc code=end

