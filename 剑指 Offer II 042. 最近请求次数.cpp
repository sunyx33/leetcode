class RecentCounter {
public:
    RecentCounter() {

    }
    
    int ping(int t) {
        m_que.push(t);
        while(m_que.front() < t - 3000) m_que.pop();
        return m_que.size();
    }
private:
    queue<int> m_que;
};