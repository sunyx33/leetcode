/*
 * @lc app=leetcode.cn id=239 lang=cpp
 *
 * [239] 滑动窗口最大值
 */
#include <deque>
#include <vector>

using namespace std;
// @lc code=start
class Myque {
    public:
    deque<int> que;
    
    int front(){
        return que.front();
    }

    void pop(int value){
        if(!que.empty() && value == que.front()){
            que.pop_front();
        }
    }

    void push(int value){
        while(!que.empty() && value > que.back()){
            que.pop_back();
        }
        que.push_back(value);
    }
};

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        Myque que;
        vector<int> res;
        for (int i = 0; i < k; i++){    
            que.push(nums[i]);
        }
        res.push_back(que.front());
        for (int i = k; i < nums.size(); i++)
        {
            que.pop(nums[i-k]);
            que.push(nums[i]);
            res.push_back(que.front());
        }
        
        return res;              
    }
};
// @lc code=end

int main(){
    vector<int> nums = {1,3,-1,-3,5,3,6,7};
    Solution sol;
    vector<int> res = sol.maxSlidingWindow(nums, 3);
    
    return 0;
}

