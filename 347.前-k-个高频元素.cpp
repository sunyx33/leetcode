/*
 * @lc app=leetcode.cn id=347 lang=cpp
 *
 * [347] 前 K 个高频元素
 */
#include<unordered_map>
#include<vector>
#include<queue>


using namespace std;
// @lc code=start
class Solution {
    // 小顶堆的排序方法
    class mycomparison {
        public:
            // 运算符重载
            // 参数1是比较者，参数2是被比较者，返回true说明参数1优先级高，也就是说，频率越大优先级越高
            // 乍一看这个逻辑反了，其实原因是优先级队列从队尾（优先级最小的）pop，所以和堆这个刚好反着来
            bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) {
                return lhs.second > rhs.second;
            }
    };
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // 1. 统计元素出现的频率，计入unordered_map:
        unordered_map<int, int> map;  // map<nums[i], 出现的次数>
        for (int i = 0; i < nums.size(); i++) {
            //使用 [] 运算符访问一个未出现在 std::unordered_map<int, int> 中的键会导致该键被插入到 std::unordered_map<int, int> 中，并将对应的值初始化为默认值，对于 int 类型的值，默认值为0。
            map[nums[i]]++;
        }

        // 对频率排序, 定义一个大小为k的小顶堆
        // 参数 1：pair<int, int>，表明该小顶堆的元素类型
        // 参数 2：vector<pair<int, int>>，底层容器的类型，这里使用 vector 作为底层容器
        // 参数 3：mycomparison， 比较函数的类型
        priority_queue<pair<int, int>, vector<pair<int, int>>, mycomparison> pri_que;

        // 用固定大小为k的小顶堆，扫遍所有频率的数值
        for (unordered_map<int, int>::iterator it = map.begin(); it != map.end(); it++) {
            pri_que.push(*it);
            if(pri_que.size() > k) {
                pri_que.pop();
            }
        }

        vector<int> result(k);
        for(int i = k - 1; i >= 0; i--) {
            result[i] = pri_que.top().first;
            pri_que.pop();
        }

        return result;
    }
};
// @lc code=end

