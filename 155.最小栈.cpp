/*
 * @lc app=leetcode.cn id=155 lang=cpp
 *
 * [155] 最小栈
 */

// @lc code=start
class MinStack {
public:
    /** initialize your data structure here. */
    stack<int> sta;
    stack<int> minsta;
    MinStack() {
    }
    
    void push(int x) {
        sta.push(x);
        if (minsta.empty()) {
            minsta.push(x);
        } else minsta.push(::min(x, minsta.top()));
    }
    
    void pop() {
        sta.pop();
        minsta.pop();
    }
    
    int top() {
        return sta.top();
    }
    
    int getMin() {
        return minsta.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
// @lc code=end

