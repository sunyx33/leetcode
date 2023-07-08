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