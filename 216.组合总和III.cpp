/*
 * @lc app=leetcode.cn id=216 lang=cpp
 *
 * [216] 组合总和 III
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
private:
vector<vector<int>> result;
vector<int> path;

void backtracking (int n, int k, int startIndex) {
    if (path.size() == k - 1) {
        if (10 > n && n >= startIndex ) {
            path.push_back(n);
            result.push_back(path);
            path.pop_back();
            return;
        } else return;
    }
    // 注意这里的边界条件：由于内层递归一定比外层大，所以进行剪枝
    // 也就说，如果当前位置之后的元素个数（包括当前）少于所需元素个数，就不该继续搜索了
    // 例如：取三个元素，则第一层:[1, 7], 第二层[2, 8]，第三层[3, 9]
    for (int i = startIndex; i <= 9 - (k - path.size()) + 1; i++) {
        path.push_back(i);
        // n - i 实际记录了一路走下来的sum，换言之，在最后一层n-i这个元素就是最后一块拼图
        backtracking(n - i, k, i + 1);
        path.pop_back();
    }    
}

public:
    vector<vector<int>> combinationSum3(int k, int n) {
        backtracking(n, k, 1);
        return result;
    }
};
// @lc code=end

int main(){
    Solution sol;
    sol.combinationSum3(9, 45);
    return 0;
}

