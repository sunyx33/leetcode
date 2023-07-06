/*
 * @lc app=leetcode.cn id=129 lang=cpp
 *
 * [129] 求根节点到叶节点数字之和
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
class Solution {
public:
    void backtrcking(TreeNode* root, string& path, int& result) {
        path += to_string(root->val);
        if(!root->left && !root->right) {
            result += stoi(path);
        } else {
            if(root->left) backtrcking(root->left, path, result);
            if(root->right) backtrcking(root->right, path, result);
        }
        path.erase(path.size() - 1);
    }

    int sumNumbers(TreeNode* root) {
        int result = 0;
        string path = "";
        backtrcking(root, path, result);
        return result;
    }
};
// @lc code=end

