/*
 * @lc app=leetcode.cn id=919 lang=cpp
 *
 * [919] 完全二叉树插入器
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
class CBTInserter {
public:
    CBTInserter(TreeNode* root) {
        m_root = root;
        TreeNode* cur = root;
        m_que.push(root);
        while(m_que.front()->left || m_que.front()->right) {
            if(m_que.front()->left && m_que.front()->right) {
                m_que.push(m_que.front()->left);
                m_que.push(m_que.front()->right);
                m_que.pop();
            } else {
                m_que.push(m_que.front()->left);
                break;
            }
        }
    }
    
    int insert(int v) {
        TreeNode* node = new TreeNode(v);
        int ret = m_que.front()->val;
        if(!m_que.front()->left) m_que.front()->left = node;
        else {
            m_que.front()->right = node;
            m_que.pop();
        }
        m_que.push(node);
        return ret;
    }
    
    TreeNode* get_root() {
        return m_root;
    }
private:
    TreeNode* m_root;
    queue<TreeNode*> m_que;
};
/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(val);
 * TreeNode* param_2 = obj->get_root();
 */
// @lc code=end

