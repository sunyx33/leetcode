/*
 * @lc app=leetcode.cn id=654 lang=cpp
 *
 * [654] 最大二叉树
 */
#include <vector>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    // 找出数组中最大元素的下标
    int findMaxIdx (vector<int> nums) {
        auto max_it = max_element(nums.begin(), nums.end());
        return distance(nums.begin(), max_it);
    }

    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        if (nums.size() == 0) return nullptr;

        TreeNode* node;
        int maxIdx;
        // 找到当前数组最大值，建立节点
        if (nums.size() > 1) {
            maxIdx = findMaxIdx(nums);
            node = new TreeNode(nums[maxIdx]);
        } else {
            node = new TreeNode(nums[0]);
            return node;
        } 


        // 左：[begin, maxIdx)
        vector<int> leftNums(nums.begin(), nums.begin() + maxIdx);
        // 右：[maxIdx + 1, end)
        vector<int> rightNums(nums.begin() + maxIdx + 1, nums.end());

        // 在左数组上构建左子树
        node->left = constructMaximumBinaryTree(leftNums);
        // 在右数组上构建右子树
        node->right = constructMaximumBinaryTree(rightNums);

        return node;
    }
};
// @lc code=end

