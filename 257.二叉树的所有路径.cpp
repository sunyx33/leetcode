/*
 * @lc app=leetcode.cn id=257 lang=cpp
 *
 * [257] 二叉树的所有路径
 */
#include <vector>
#include <string>

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
    void traversal(TreeNode* cur, vector<int>& path, vector<string>& result) {
        // 记录当前节点
        path.push_back(cur->val);

        // 如果当前节点是叶子节点，就将path中的数据转换为string
        if (cur->left == nullptr && cur->right == nullptr) {
            string sPath;
            for(int i = 0; i < path.size() - 1; i++) {
                sPath += to_string(path[i]);
                sPath += "->";
            }
            sPath += to_string(path[path.size() - 1]);
            result.push_back(sPath);
            return;
        }

        // 当前节点有孩子，进孩子，直至到头，返回并删除孩子在path中的值（也就做到了回溯）
        if (cur->left) {
            traversal(cur->left, path, result);
            path.pop_back();
        }

        if (cur->right) {
            traversal(cur->right, path, result);
            path.pop_back();
        }
    }

    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> result;
        vector<int> path;
        if (root == nullptr) {
            return result;
        }
        traversal(root, path, result);
        return result;
    }
};
// @lc code=end

