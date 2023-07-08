class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        if(!root) return false;
        if(m_set.find(k - root->val) != m_set.end()) return true;
        else {
            m_set.emplace(root->val);
            return findTarget(root->left, k) || findTarget(root->right, k);
        }
        return false;
    }
private:
    unordered_set<int> m_set;
};