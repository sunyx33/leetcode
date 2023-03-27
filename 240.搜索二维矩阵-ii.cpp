/*
 * @lc app=leetcode.cn id=240 lang=cpp
 *
 * [240] 搜索二维矩阵 II
 */

// @lc code=start
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.size() == 0 || matrix[0].size() == 0) return false;
        int row = 0;
        int col = matrix[0].size() - 1;
        while(row < matrix.size() && col >= 0) {
            if(matrix[row][col] > target) col --;
            else if (matrix[row][col] < target) row ++;
            else return true;
        }   
        return false;
    }
};
// @lc code=end

