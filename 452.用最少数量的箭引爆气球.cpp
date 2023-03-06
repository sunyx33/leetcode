/*
 * @lc app=leetcode.cn id=452 lang=cpp
 *
 * [452] 用最少数量的箭引爆气球
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    }
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.size() == 0) return 0;
        sort(points.begin(), points.end(), cmp);

        int result = 1; // points 不为空至少需要一支箭
        for (int i = 1; i < points.size(); i++) {
            if (points[i][0] > points[i - 1][1]) {  // 气球i和气球i-1不挨着，注意这里不是>=
                result ++; // 需要一支箭
            }
            else { // i 与 i - 1 重叠
                // 更新重叠气球的最小又边界，result不加，看下一个和缩小后的右边界是否有重叠，若还有，继续缩小；若没有，result ++
                points[i][1] = min(points[i - 1][1], points[i][1]); 
            }
        }
        return result;    
    }   
};
// @lc code=end

