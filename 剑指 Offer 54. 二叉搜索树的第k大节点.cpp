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
    int kthLargest(TreeNode* root, int k) {
        inorder(root, k);
        return res;
    }

private:
    int res;
    int cnt;
    void inorder(TreeNode* cur, int k) {
        if (!cur) return;
        if(cnt != k) inorder(cur->right, k);
        if(++cnt == k) {
            res = cur->val;
        }
        if(cnt != k) inorder(cur->left, k);
    }
};