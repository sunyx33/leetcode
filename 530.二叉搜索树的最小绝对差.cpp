/*
 * @lc app=leetcode.cn id=530 lang=cpp
 *
 * [530] 二叉搜索树的最小绝对差
 */
#include <algorithm>

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
    int result = __INT_MAX__;
    TreeNode* pre = nullptr;
    void traversal (TreeNode* cur) {
        if (cur == nullptr) return;

        traversal(cur->left);
        if (pre != nullptr) result = min(result, cur->val - pre->val);
        pre = cur;
        traversal(cur->right);
    }
    int getMinimumDifference(TreeNode* root) {
        traversal(root);
        return result;        
    }
};
// @lc code=end

// int main () {
//     TreeNode* node4 = new TreeNode(4);
//     TreeNode* node7 = new TreeNode(7);
//     TreeNode* node5 = new TreeNode(5, node4, node7);
//     Solution sol;
//     int res = sol.getMinimumDifference(node5);
//     return 0;
// }

