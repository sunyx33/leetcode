class CQueue {
public:
    stack<int> appendSta;
    stack<int> deleteSta;
    CQueue() {
    }
    
    void appendTail(int value) {
        appendSta.push(value);
    }
    
    int deleteHead() {
        int result = -1;
        if (!deleteSta.empty()) {
            result = deleteSta.top();
            deleteSta.pop();
        } else {
            int tmp;
            while (!appendSta.empty()) {
                tmp = appendSta.top();
                appendSta.pop();
                deleteSta.push(tmp);
            }
            if (!deleteSta.empty()) {
                result = deleteSta.top();
                deleteSta.pop();
            }
        }
        return result;
    }
};

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */