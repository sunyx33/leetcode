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
