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
    vector<int> levelOrder(TreeNode* root) {
        vector<int> result;
        queue<TreeNode*> que;
        if (root != nullptr) que.push(root);
        while (!que.empty()) {
            TreeNode* node = que.front();
            result.push_back(node->val);
            que.pop();
            if (node->left != nullptr) que.push(node->left);
            if (node->right != nullptr) que.push(node->right);
        }
        return result;
    }
};