/*
 * @lc app=leetcode.cn id=173 lang=cpp
 *
 * [173] 二叉搜索树迭代器
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
class BSTIterator {
public:
    BSTIterator(TreeNode* root) {
        dummy = new TreeNode(-1);
        pre = dummy;
        cur = dummy;
        flatten(root);
    }

    void flatten(TreeNode* root) {
        if(!root) return;
        flatten(root->left);
        pre->right = root;
        root->left = nullptr;
        pre = root;
        flatten(root->right); 
    }
    
    int next() {
        cur = cur->right;
        return cur->val;
    }
    
    bool hasNext() {
        return cur->right != nullptr;
    }
private:
    TreeNode* dummy;
    TreeNode* pre;
    TreeNode* cur;
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
// @lc code=end

