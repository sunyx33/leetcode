/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if (A == nullptr || B == nullptr) return false; // 空树不是任意树的子树
        if (isEqual(A, B)) return true; // 如果以A、B为根节点的两棵树相等，返回true
        else return isSubStructure(A->left, B) || isSubStructure(A->right, B); // 否则检查A的左子树、右子树是否有和B相等的树（前序）
    }

    // 比较以A、B为根节点的树是否相等
    bool isEqual(TreeNode* A, TreeNode* B) {
        if (B == nullptr) return true; // 终止条件：B比到了空节点，说明上面的结点都匹配上了
        if (A == nullptr) return false; // 终止条件：A比到了空节点但B还有，说明不匹配
        if (A->val == B->val) return isEqual(A->left, B->left) && isEqual(A->right, B->right); // 前序
        else return false; // 发现不相等，直接终止
    }
};