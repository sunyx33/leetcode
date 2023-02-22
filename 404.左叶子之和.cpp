/*
 * @lc app=leetcode.cn id=404 lang=cpp
 *
 * [404] 左叶子之和
 */
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
    void preOrder(TreeNode* cur, bool isLeft, int& record) {
        if (cur == nullptr) { 
            return;
        }
        if (isLeft == true && cur->left == nullptr && cur->right == nullptr) {
            record += cur->val;
        }
        
        preOrder(cur->left, true, record); 
        preOrder(cur->right, false, record);
    }

    int sumOfLeftLeaves(TreeNode* root) {
        int record = 0;
        preOrder(root, false, record);
        return record;
    }
};
// @lc code=end

