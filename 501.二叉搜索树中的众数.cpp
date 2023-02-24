/*
 * @lc app=leetcode.cn id=501 lang=cpp
 *
 * [501] 二叉搜索树中的众数
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
    TreeNode* pre = nullptr;
    int maxCount = 0;
    int count = 0;
    void traversal (TreeNode* cur, vector<int>& res) {
        if (cur == nullptr) return;

        traversal(cur->left, res);

        if(pre == nullptr) {
            count = 1;
            res.push_back(cur->val);
            maxCount = 1;
        } else {
            if (cur->val == pre->val) count ++;
            else count = 1;

            if (count > maxCount) {
                    res.clear();
                    res.push_back(cur->val);
                    maxCount = count;
                }
            else if (count == maxCount) {
                res.push_back(cur->val);
            }

        }
        pre = cur;

        traversal(cur->right, res);

        return;
    }

    vector<int> findMode(TreeNode* root) {
        vector<int> res;
        traversal(root, res);
        return res;
    }
};
// @lc code=end
// int main () {
//     TreeNode* node1 = new TreeNode(2);
//     TreeNode* node2 = new TreeNode(2, node1, nullptr);
//     TreeNode* node3 = new TreeNode(1, nullptr, node2);

//     Solution sol;
//     sol.findMode(node3);
//     return 0;
// }
