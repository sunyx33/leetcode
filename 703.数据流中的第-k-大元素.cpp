/*
 * @lc app=leetcode.cn id=703 lang=cpp
 *
 * [703] 数据流中的第 K 大元素
 */
#include <vector>
#include <queue>
using namespace std;
// @lc code=start
class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) {
        m_k = k;
        for(int n : nums) {
            m_heap.push(n);
            if(m_heap.size() > m_k) m_heap.pop();
        }
    }
    
    int add(int val) {
        m_heap.push(val);
        if(m_heap.size() > m_k) m_heap.pop();
        return m_heap.top();
    }

private:
    priority_queue<int, vector<int>, greater<int>> m_heap;
    int m_k;
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
// @lc code=end

