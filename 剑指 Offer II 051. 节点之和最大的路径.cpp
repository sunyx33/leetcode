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
    int maxPathSum(TreeNode* root) {
        int result = INT_MIN;
        getMax(root, result);
        return result;
    }
    int getMax(TreeNode* root, int& result) {
        if(!root) return 0;
        int left = max(getMax(root->left, result), 0);
        int right = max(getMax(root->right, result), 0);
        result = max(result, left + right + root->val);
        return max(left, right) + root->val;
    }

};