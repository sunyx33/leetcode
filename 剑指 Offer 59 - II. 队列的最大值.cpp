class MaxQueue {
public:
    deque<int> maxque;
    queue<int> que;
    MaxQueue() {

    }
    
    int max_value() {
        return maxque.empty() ? -1 : maxque.front();
    }
    
    void push_back(int value) {
        while(!maxque.empty() && value > maxque.back()) {
            maxque.pop_back();
        }
        maxque.push_back(value);
        que.push(value);
    }
    
    int pop_front() {
        if (que.empty()) return -1;
        int value = que.front();
        if(value == maxque.front()) {
            maxque.pop_front();
        }
        que.pop();
        return value;
    }
};

/**
 * Your MaxQueue object will be instantiated and called as such:
 * MaxQueue* obj = new MaxQueue();
 * int param_1 = obj->max_value();
 * obj->push_back(value);
 * int param_3 = obj->pop_front();
 */