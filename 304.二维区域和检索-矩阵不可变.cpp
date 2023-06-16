/*
 * @lc app=leetcode.cn id=304 lang=cpp
 *
 * [304] 二维区域和检索 - 矩阵不可变
 */
#include <vector>
using namespace std;
// @lc code=start
class NumMatrix {
public:
    NumMatrix(vector<vector<int>>& matrix) {
        m_matrix = vector<vector<int>>(matrix.size() + 1, vector<int>(matrix[0].size() + 1, 0));
        for(int row = 1; row < m_matrix.size(); row ++) {
            for(int col = 1; col < m_matrix[0].size(); col ++){
                m_matrix[row][col] = m_matrix[row - 1][col] + m_matrix[row][col - 1] - m_matrix[row - 1][col - 1] + matrix[row - 1][col - 1];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        row1 ++;
        col1 ++;
        row2 ++;
        col2 ++;
        int result = m_matrix[row2][col2] - m_matrix[row2][col1 - 1] - m_matrix[row1 - 1][col2] + m_matrix[row1 - 1][col1 - 1];
        return result;
    }
private:
vector<vector<int>> m_matrix;
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
// @lc code=end

