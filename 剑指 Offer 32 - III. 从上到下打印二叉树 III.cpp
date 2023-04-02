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
    vector<vector<int>> levelOrder(TreeNode* root) {
        deque<TreeNode*> que;
        vector<vector<int>> result;
        bool flag = true; 
        if (root != nullptr) que.push_back(root);
        while (!que.empty()) {
            int size = que.size();
            vector<int> vec;
            for (int i = 0; i < size; i ++) {
                if (flag) { // true代表单数层，此时从队首读，其子结点从左到右加入队尾
                    TreeNode* node = que.front();
                    que.pop_front();
                    vec.push_back(node->val);
                    if (node->left != nullptr) que.push_back(node->left);
                    if (node->right != nullptr) que.push_back(node->right);
                } else { // false代表双数层，此时从队尾读，其子节点从右到左加入队头
                    TreeNode* node = que.back();
                    que.pop_back();
                    vec.push_back(node->val);
                    if(node->right != nullptr) que.push_front(node->right);
                    if(node->left != nullptr) que.push_front(node->left);
                } 
            }
            result.push_back(vec);
            flag = !flag;
        }
        return result;
    }
};