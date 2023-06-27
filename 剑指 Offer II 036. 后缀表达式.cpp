class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> sta;
        for(string s : tokens) {
            if(s == "+" || s == "-" || s == "*" || s == "/") {
                // num2 - num1
                int num1 = sta.top();
                sta.pop();
                int num2 = sta.top();
                sta.pop();
                int result = 0;
                if(s == "+") result = num2 + num1;
                else if(s == "-") result = num2 - num1;
                else if(s == "*") result = num2 * num1;
                else result = num2 / num1;
                sta.push(result); 
            } else {
                sta.push(stoi(s));
            }
        }
        return sta.top();
    }
};