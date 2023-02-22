/*
 * @lc app=leetcode.cn id=112 lang=cpp
 *
 * [112] 路径总和
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
public:
    void preOrder(TreeNode* cur, int& sum, int targetSum, bool& isFind){
        // 进行累加的操作
        sum += cur->val;

        // 遇到叶子节点
        if (cur->left == nullptr && cur->right == nullptr) {
            if (sum == targetSum) {
                // 找到，设置标志位，将跳过接下来所有的递归
                isFind = true;
                return;
            }
            else {
                // 回溯
                sum -= cur->val;
                return;
            }            
        }
        
        // 不是叶子节点
        if (cur->left) {
            preOrder(cur->left, sum, targetSum, isFind);
            if (isFind == true) {
                return;
            }
        }
        
        if (cur->right) {
            preOrder(cur->right, sum, targetSum, isFind);
            if (isFind == true) {
                return;
            }
        }
        // 这个节点以下都看过了，回溯
        sum -= cur->val; 

        return;
    } 

    bool hasPathSum(TreeNode* root, int targetSum) {
        bool isFind = false;
        int sum = 0;
        if (root == nullptr) {
            return false;
        }
        preOrder(root, sum, targetSum, isFind);
        return isFind;
    }
};
// @lc code=end

int main() {
    TreeNode* node7 = new TreeNode(7);
    TreeNode* node2 = new TreeNode(2);
    TreeNode* node1 = new TreeNode(1);
    TreeNode* node13 = new TreeNode(13, nullptr, node1);
    TreeNode* node4_r = new TreeNode(4);
    TreeNode* node8 = new TreeNode(8, node13, node4_r);
    TreeNode* node11 = new TreeNode(11, node7, node2);
    TreeNode* node4_l = new TreeNode(4, node11, nullptr);
    TreeNode* node5 = new TreeNode(5, node4_l, node8);

    Solution sol;

    bool isFind = sol.hasPathSum(node5, 22);
    
    




    return 0;
}

