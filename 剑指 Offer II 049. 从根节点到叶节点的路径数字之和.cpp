class Solution {
public:
    void backtrcking(TreeNode* root, string& path, int& result) {
        path += to_string(root->val);
        if(!root->left && !root->right) {
            result += stoi(path);
        } else {
            if(root->left) backtrcking(root->left, path, result);
            if(root->right) backtrcking(root->right, path, result);
        }
        path.erase(path.size() - 1);
    }

    int sumNumbers(TreeNode* root) {
        int result = 0;
        string path = "";
        backtrcking(root, path, result);
        return result;
    }
};