/*
 * @lc app=leetcode.cn id=496 lang=cpp
 *
 * [496] 下一个更大元素 I
 */
#include <unordered_map>
#include <stack>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> umap;
        for (int i = 0; i < nums1.size(); i++) {
            umap[nums1[i]] = i;
        }

        vector<int> result(nums1.size(), -1);
        stack<int> sta;
        sta.push(nums2[0]);
        for (int i = 1; i < nums2.size(); i++) {
            if (nums2[i] <= sta.top()) sta.push(nums2[i]);
            else {
                while (!sta.empty() && nums2[i] > sta.top()) {
                    if (umap.count(sta.top()) > 0) { // 查看nums1里有没有这个元素
                        result[umap[sta.top()]] = nums2[i];
                    }
                    sta.pop();
                }
                sta.push(nums2[i]);
            }
        }
        return result;
    }
};
// @lc code=end

