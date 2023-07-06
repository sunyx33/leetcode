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
    TreeNode* res;
    void inorder(TreeNode* root, TreeNode* p) {
        if(!root || res) return;
        inorderSuccessor(root->left, p);
        cout << root->val << endl;
        if(!res && root->val > p->val) {
            res = root;
            return;
        }
        inorderSuccessor(root->right, p);
    }
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        inorder(root, p);
        return res;
    }
};