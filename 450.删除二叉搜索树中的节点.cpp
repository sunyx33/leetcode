/*
 * @lc app=leetcode.cn id=450 lang=cpp
 *
 * [450] 删除二叉搜索树中的节点
 */
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
    TreeNode* deleteNode(TreeNode* root, int key) {
        // 情况一：没有要删除的结点
        if (root == nullptr) return root;
        if (root->val == key) {
            // 情况二：删除的结点为叶子结点：直接删除
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                return nullptr;
            }

            // 情况三：删除的结点仅有右孩子：删除，右孩子补位
            else if (root->left == nullptr && root->right != nullptr) {
                TreeNode* retNode = root->right;
                delete root;
                return retNode;
            }

            // 情况四：删除的结点仅有左孩子：删除，左孩子补位
            else if (root->left != nullptr && root->right == nullptr) {
                TreeNode* retNode = root->left;
                delete root;
                return retNode;
            }

            // 情况五：删除的结点有左右孩子：则将删除节点的左子树放到删除节点的右子树的最左面节点的左孩子的位置
            // 并返回删除节点右孩子为新的根节点。
            else
            {
                // 找右子树的最左结点
                TreeNode* cur = root->right;
                while (cur->left)
                {
                    cur = cur->left;
                }
                cur->left = root->left;  // 给最左结点赋左孩子
                TreeNode* temp = root;  // 暂存一下原root，以便删除
                root = root->right; // 替换原root
                delete temp;
                return root;
            }
            
        }

        if (root->val > key) root->left = deleteNode(root->left, key);
        if (root->val < key) root->right = deleteNode(root->right, key);
        return root;
    }
};
// @lc code=end

