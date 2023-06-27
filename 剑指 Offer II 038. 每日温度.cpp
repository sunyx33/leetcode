class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> sta;
        vector<int> result(temperatures.size(), 0);
        sta.push(0);
        for(int i = 1; i < temperatures.size(); i++) {
            if(temperatures[sta.top()] >= temperatures[i]) sta.push(i);
            else {
                while(!sta.empty() && temperatures[sta.top()] < temperatures[i]) {
                    result[sta.top()] = i - sta.top();
                    sta.pop();
                }
                sta.push(i);
            }
        }
        return result;
    }
};