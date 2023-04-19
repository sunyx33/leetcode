class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> sta;
        int cur = 0;
        for(int num : pushed) {
            sta.push(num);
            while(cur < popped.size() && !sta.empty() && sta.top() == popped[cur]) {
                sta.pop();
                cur ++;
            }
        }
        return cur == popped.size();
    }
};