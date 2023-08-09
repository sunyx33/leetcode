/*
 * @lc app=leetcode.cn id=1122 lang=cpp
 *
 * [1122] 数组的相对排序
 */
#include <unordered_map>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        unordered_map<int, int> arr2Map;
        for(int i = 0; i < arr2.size(); i++) arr2Map[arr2[i]] = i;
        sort(arr1.begin(), arr1.end(), [&](int x, int y){
            if(arr2Map.count(x)) return arr2Map.count(y) ? arr2[x] < arr2[y] : true;
            else return arr2Map.count(y) ? false : x < y;
        });
        return arr1;
    }
};
// @lc code=end

