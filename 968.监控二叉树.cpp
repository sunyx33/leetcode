/*
 * @lc app=leetcode.cn id=968 lang=cpp
 *
 * [968] 监控二叉树
 */
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
private:
    int result;
    int traversal(TreeNode* cur) {
        // 空节点，有覆盖
        if (cur == nullptr) return 2;

        int left = traversal(cur->left);
        int right = traversal(cur->right);

        // 情况一 左右子结点都有覆盖
        if (left == 2 && right == 2) return 0;

        // 情况二
        // left == 0 && right == 0 左右节点无覆盖
        // left == 1 && right == 0 左节点有摄像头，右节点无覆盖
        // left == 0 && right == 1 左节点有无覆盖，右节点摄像头
        // left == 0 && right == 2 左节点无覆盖，右节点覆盖
        // left == 2 && right == 0 左节点覆盖，右节点无覆盖
        if (left == 0 || right == 0) {
            result ++;
            return 1;
        }

        // 情况三
        // left == 1 && right == 2 左节点有摄像头，右节点有覆盖
        // left == 2 && right == 1 左节点有覆盖，右节点有摄像头
        // left == 1 && right == 1 左右节点都有摄像头
        if (left == 1 || right == 1) return 2;

        // 实际不会走到这里的，上面已经覆盖了所有情况
        return -1;
    }
public:
    int minCameraCover(TreeNode* root) {
        result = 0;
        // 情况四 root无覆盖
        if (traversal(root) == 0) {
            result ++;
        }
        return result;
    }
};
// @lc code=end

