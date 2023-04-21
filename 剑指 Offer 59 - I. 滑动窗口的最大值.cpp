class Myque {
public:
    deque<int> que;

    int front() {
        return que.front();
    }

    void pop(int val) {
        if(!que.empty() && val == que.front()) {
            que.pop_front();
        }
    }

    void push(int val) {
        while(!que.empty() && val > que.back()) {
            que.pop_back();
        }
        que.push_back(val);
    }
};

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        Myque que;
        vector<int> res;
        for(int i = 0; i < k; i++) {
            que.push(nums[i]);
        }
        res.push_back(que.front());
        for(int i = k; i < nums.size(); i++) {
            que.pop(nums[i - k]);
            que.push(nums[i]);
            res.push_back(que.front());
        }
        return res;
    }
};