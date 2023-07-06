/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        queue<TreeNode*> que;
        if(root) que.push(root);
        string result = "";
        while(!que.empty()){
            int size = que.size();
            while(size --){
                if(!que.front()) {
                    result += "null,";
                    que.pop();
                } else{
                    result += to_string(que.front()->val) + ",";
                    if(que.front()->left) que.push(que.front()->left);
                    else que.push(nullptr);
                    if(que.front()->right) que.push(que.front()->right);
                    else que.push(nullptr);
                    que.pop();
                }
            }
        }
        return result;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<string> dataArray;
        string str;
        for (auto& ch : data) {
            if (ch == ',') {
                dataArray.push_back(str);
                str.clear();
            } else {
                str.push_back(ch);
            }
        }
        
        if (!str.empty()) {
            dataArray.push_back(str);
            str.clear();
        }
        queue<TreeNode*> que;
        TreeNode* root = nullptr;
        if(!dataArray.empty()) root = new TreeNode(stoi(dataArray[0]));
        que.push(root);
        int cnt = 0;
        for(int i = 1; i < dataArray.size(); i++) {
            TreeNode* node = str2Node(dataArray[i]);
            if(cnt == 0) {
                que.front()->left = node;
                que.push(node);
                cnt ++;
            } else if(cnt == 1) {
                que.front()->right = node;
                que.push(node);
                cnt ++;
            } else {
                que.pop();
                while(que.front() == nullptr) que.pop();
                que.front()->left = node;
                que.push(node);
                cnt = 1;
            }
        }
        return root;
    }

    TreeNode* str2Node(string& s) {
        TreeNode* node;
        if(s == "null") return nullptr;
        else node = new TreeNode(stoi(s));
        return node;
    } 


};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));