/*
 * @lc app=leetcode.cn id=167 lang=cpp
 *
 * [167] 两数之和 II - 输入有序数组
 */

// @lc code=start
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> result(2);
        for(int i = 0; i < numbers.size(); i++) {
            if(i > 0 && numbers[i] == numbers[i - 1]) continue;
            for(int j = i + 1; j < numbers.size(); j++) {
                if(j > i + 1 && numbers[j] == numbers[j - 1]) continue;
                if(numbers[i] + numbers[j] < target) continue;
                else if(numbers[i] + numbers[j] > target) break;
                else {
                    result[0] = i + 1;
                    result[1] = j + 1;
                    return result;
                }
            }
        }
        return result;
    }
};
// @lc code=end

