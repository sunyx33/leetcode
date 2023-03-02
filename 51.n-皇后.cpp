/*
 * @lc app=leetcode.cn id=51 lang=cpp
 *
 * [51] N 皇后
 */
#include <vector>
#include <string>

using namespace std;
// @lc code=start
class Solution {
private:
    vector<vector<string>> result;
    void backtracking(int n, int row, vector<string>& chessboard) {
        if (row == n) {
            result.push_back(chessboard);
            return;
        }

        for(int col = 0; col < n; col ++) {
            if (isValid(row, col, chessboard, n)) {
                chessboard[row][col] = 'Q';
                backtracking(n, row + 1, chessboard);
                chessboard[row][col] = '.';
            }
        }
    }

    bool isValid (int row, int col, vector<string>& chessboard, int n) {
        // 检查列
        for (int i = 0; i < row; i++) {
            if (chessboard[i][col] == 'Q') return false;
        }

        // 检查第一象限
        for (int i = row, j = col; i >= 0 && j < n ;i--, j++ ) {
            if (chessboard[i][j] == 'Q') return false; 
        }

        // 检查第二象限
        for (int i = row, j = col; i >= 0 && j >= 0 ;i--, j-- ) {
            if (chessboard[i][j] == 'Q') return false; 
        }

        // 检查第三象限
        for (int i = row, j = col; i < n && j >= 0 ;i++, j-- ) {
            if (chessboard[i][j] == 'Q') return false; 
        }

        // 检查第四象限
        for (int i = row, j = col; i < 0 && j < 0 ;i++, j++ ) {
            if (chessboard[i][j] == 'Q') return false; 
        }    

        return true;    
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        vector<string> chessboard(n, string(n, '.'));
        backtracking(n, 0, chessboard);
        return result;
    }
};
// @lc code=end

