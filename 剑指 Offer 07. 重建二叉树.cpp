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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return travelsal(preorder, inorder);
    }

    TreeNode* travelsal(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.size() == 0) return nullptr;

        int rootValue = preorder[0];
        TreeNode* root = new TreeNode(rootValue);

        if (preorder.size() == 1)return root;

        int delimiterIndex;
        for(delimiterIndex = 0; delimiterIndex < inorder.size(); delimiterIndex ++) {
            if (inorder[delimiterIndex] == rootValue) break;
        }

        vector<int> leftInorder(inorder.begin(), inorder.begin() + delimiterIndex);
        vector<int> rightInorder(inorder.begin() + delimiterIndex + 1, inorder.end());

        vector<int> leftPreorder(preorder.begin() + 1, preorder.begin() + leftInorder.size() + 1);
        vector<int> rightPreorder(preorder.begin() + leftInorder.size() + 1, preorder.end());

        root->left = travelsal(leftPreorder, leftInorder);
        root->right = travelsal(rightPreorder, rightInorder);

        return root;
    }
};