class Solution {
public:
    bool verifyPostorder(vector<int>& postorder) {
        if(postorder.size() <= 2) return true;
        int i = 0;
        int rootValue = postorder[postorder.size() - 1];
        for( ; i < postorder.size() - 1; i++) {
            if(postorder[i] > rootValue) break;
        }
        int m = i;
        for( ; i < postorder.size() - 1; i++) {
            if(postorder[i] < rootValue) break;
        }
        if(i < postorder.size() - 1) return false;

        vector<int> leftPostorder(postorder.begin(), postorder.begin() + m);
        vector<int> rightPostorder(postorder.begin() + m, postorder.end() - 1);

        return verifyPostorder(leftPostorder) && verifyPostorder(rightPostorder);
    }
};