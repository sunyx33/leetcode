class MovingAverage {
public:
    /** Initialize your data structure here. */
    MovingAverage(int size) {
        m_size = size;
        m_sum = 0;
    }
    
    double next(int val) {
        if(m_que.size() == m_size) {
            int del = m_que.front();
            m_que.pop();
            m_sum -= del;
        }
        m_que.push(val);
        m_sum += val;
        return static_cast<double>(m_sum) / m_que.size();
    }
private:
    queue<int> m_que;
    int m_size;
    int m_sum;
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */