class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        vector<int> result;
        int layer = 0;
        queue<TreeNode*> que;
        if(root) que.push(root);
        while(!que.empty()) {
            int max = INT_MIN;
            int size = que.size();
            while(size --) {
                if(que.front()->val > max) max = que.front()->val;
                if(que.front()->left) que.push(que.front()->left);
                if(que.front()->right) que.push(que.front()->right);
                que.pop();
            }
            result.push_back(max);
        }
        return result;
    }
};