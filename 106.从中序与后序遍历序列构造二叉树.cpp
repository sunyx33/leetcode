/*
 * @lc app=leetcode.cn id=106 lang=cpp
 *
 * [106] 从中序与后序遍历序列构造二叉树
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
    TreeNode* traversal(vector<int>& inorder, vector<int>& postorder) {
        // 第一步
        if (postorder.size() == 0) return nullptr;

        // 第二步：后序数组最后一个元素当作中序数组分割点
        int rootValue = postorder[postorder.size() - 1];
        TreeNode* root = new TreeNode(rootValue);

        // 叶子节点（终止条件）
        if (postorder.size() == 1) return root;

        // 第三步：找切割点
        int delimiterIndex;
        for (delimiterIndex = 0; delimiterIndex < inorder.size(); delimiterIndex ++) {
            if (inorder[delimiterIndex] == rootValue) break;
        }

        // 第四步：切割中序数组，得到中序左数组与中序右数组，左闭右开
        // [0, delimiterIndex)
        vector<int> leftInorder(inorder.begin(), inorder.begin() + delimiterIndex);
        // [delimiterIndex, end)
        vector<int> rightInorder(inorder.begin() + delimiterIndex + 1, inorder.end());
        
        // 第五步：切割后序数组，得到后序左数组与后序右数组，左闭右开
        // 去掉最后一个元素，按照左右中序数组的大小来切割
        postorder.resize(postorder.size() - 1);
        vector<int> leftPostorder(postorder.begin(), postorder.begin() + leftInorder.size());
        vector<int> rightPostorder(postorder.begin() + leftInorder.size(), postorder.end());

        // 第六步：进入递归
        root->left = traversal(leftInorder, leftPostorder);
        root->right = traversal(rightInorder, rightPostorder);

        return root;

    }

    TreeNode* buildTree (vector<int>& inorder, vector<int>& postorder) {
        if(inorder.size() == 0 || postorder.size() == 0) return nullptr;
        return (traversal(inorder, postorder));
    }
};
// @lc code=end

