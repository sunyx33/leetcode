/*
 * @lc app=leetcode.cn id=105 lang=cpp
 *
 * [105] 从前序与中序遍历序列构造二叉树
 */
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
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
class Solution {
public:
    TreeNode* traversal(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.size() == 0) return nullptr;

        int rootValue = preorder[0];
        TreeNode* root = new TreeNode(rootValue);

        if (preorder.size() == 1) return root;

        // 找切割点
        int delimiterIndex;
        for (delimiterIndex = 0; delimiterIndex < inorder.size(); delimiterIndex ++) {
            if (inorder[delimiterIndex] == rootValue) break;
        }

        // 切割中序数组，得到中序左数组与中序右数组，左闭右开
        // [0, delimiterIndex)
        vector<int> leftInorder(inorder.begin(), inorder.begin() + delimiterIndex);
        // [delimiterIndex, end)
        vector<int> rightInorder(inorder.begin() + delimiterIndex + 1, inorder.end());
        
        // 切割后序数组，得到后序左数组与后序右数组，左闭右开
        // 去掉第一个元素，按照左右中序数组的大小来切割
        vector<int> newarr(preorder.begin() + 1, preorder.end());
        vector<int> leftPreorder(newarr.begin(), newarr.begin() + leftInorder.size());
        vector<int> rightPreorder(newarr.begin() + leftInorder.size(), newarr.end());

        // 进入递归
        root->left = traversal(leftPreorder, leftInorder);
        root->right = traversal(rightPreorder, rightInorder);

        return root;

    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(inorder.size() == 0 || preorder.size() == 0) return nullptr;
        return (traversal(preorder, inorder));
    }
};
// @lc code=end

int main() {
    Solution sol;
    vector<int> preorder = {3,9,20,15,7};
    vector<int> inorder = {9,3,15,20,7};
    sol.buildTree(preorder, inorder);
    return 0;
}
