/*
 * @lc app=leetcode.cn id=144 lang=cpp
 *
 * [144] 二叉树的前序遍历
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
#include<stack>
#include<vector>

using namespace std;
class Solution {
public:
    // void preorder(TreeNode* cur, vector<int>& res) {
    //     if (cur == nullptr) {
    //         return;
    //     }
    //     res.push_back(cur -> val);
    //     preorder(cur -> left, res);
    //     preorder(cur -> right, res);
    // }

    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        // preorder(root, res);
        // return res;
        stack<TreeNode*> sta;
        if (root == nullptr) return res;
        sta.push(root);
        while (!sta.empty()) {
            TreeNode* node = sta.top();
            sta.pop();
            res.push_back(node->val);
            if(node->right) sta.push(node->right);
            if(node->left) sta.push(node->left);
        }
        return res;
    }
};
// @lc code=end

