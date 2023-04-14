/*
 * @lc app=leetcode.cn id=113 lang=cpp
 *
 * [113] 路径总和 II
 */

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
#include <vector>
using namespace std;
class Solution {
public:
    void preorder(TreeNode* root, int targetSum, int& sum, vector<int>& path, vector<vector<int>>& result) {
        sum += root->val;
        path.push_back(root->val);
        if(sum == targetSum && root->left == nullptr && root->right == nullptr) result.push_back(path);
        if(root->left != nullptr) preorder(root->left, targetSum, sum, path, result);
        if(root->right != nullptr) preorder(root->right, targetSum, sum, path, result);

        sum -= root->val;
        path.pop_back();
    }

    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        int sum = 0;
        vector<int> path;
        vector<vector<int>> result;
        if (root != nullptr) preorder(root, targetSum, sum, path, result);
        return result;    
    }
};
// @lc code=end

