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
    bool isBalanced(TreeNode* root) {
        return maxDepth(root) != -1;
    }

    int maxDepth(TreeNode* root) {
        if(root == nullptr) return 0;
        int leftDepth = maxDepth(root->left);
        if (leftDepth == -1) return -1;
        int rightDepth = maxDepth(root->right);
        if (rightDepth == -1) return -1;
        return abs(leftDepth - rightDepth) > 1? -1 : max(leftDepth, rightDepth) + 1;
    }
};