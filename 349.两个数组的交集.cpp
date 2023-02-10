#include <vector>
#include <unordered_set>
using namespace std;
/*
 * @lc app=leetcode.cn id=349 lang=cpp
 *
 * [349] 两个数组的交集
 */

// @lc code=start
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> result_set; // 存放结果
        unordered_set<int> nums_set(nums1.begin(), nums1.end()); // 使用迭代器进行初始化，vec -> set
        for(int num : nums2){
            if(nums_set.find(num) != nums_set.end()){
                result_set.insert(num);
            }
        }

        return vector<int>(result_set.begin(), result_set.end());
    }
};
// @lc code=end

