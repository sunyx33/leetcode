/*
 * @lc app=leetcode.cn id=406 lang=cpp
 *
 * [406] 根据身高重建队列
 */
#include <vector>
#include <algorithm>
#include <list>
using namespace std;
// @lc code=start
class Solution {
public:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        if (a[0] == b[0]) return a[1] < b[1];
        return a[0] > b[0];
    }

    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort (people.begin(), people.end(), cmp); 
        list<vector<int>> que;
        for (int i = 0; i < people.size(); i++){
            int position = people[i][1];
            std::list<vector<int>>::iterator it = que.begin();
            while (position--){
                it ++;
            }
            que.insert(it, people[i]);
        }

        return vector<vector<int>>(que.begin(), que.end());
            
    }
};
// @lc code=end

