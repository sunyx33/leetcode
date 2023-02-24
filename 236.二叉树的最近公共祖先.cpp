/*
 * @lc app=leetcode.cn id=236 lang=cpp
 *
 * [236] 二叉树的最近公共祖先
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == q || root== p || root == nullptr) return root;
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        
        // 在左子树与右子树分别找到了目标
        if (left != NULL && right != NULL) return root;
        
        // 仅在右子树找到目标
        if (left == NULL && right != NULL) return right;

        // 仅在左子树找到目标
        else if (left != NULL && right == NULL) return left;

        // 没有目标
        else return nullptr;
        
    }
};
// @lc code=end

