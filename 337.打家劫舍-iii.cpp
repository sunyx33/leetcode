/*
 * @lc app=leetcode.cn id=337 lang=cpp
 *
 * [337] 打家劫舍 III
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
    vector<int> travelsal(TreeNode* cur) {
        if(cur == nullptr) return vector<int> {0, 0};
        vector<int> left = travelsal(cur->left);
        vector<int> right = travelsal(cur->right);
        vector<int> dp(2);
        dp[0] = max(left[0], left[1]) + max(right[0], right[1]);
        dp[1] = cur->val + left[0] + right[0];
        return dp;
    }

    int rob(TreeNode* root) {
        return max(travelsal(root)[0], travelsal(root)[1]);
    }
};
// @lc code=end

