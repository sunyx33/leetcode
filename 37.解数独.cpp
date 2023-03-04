/*
 * @lc app=leetcode.cn id=37 lang=cpp
 *
 * [37] 解数独
 */
#include <vector>

using namespace std;
// @lc code=start
class Solution {
private:
    bool backtracking(vector<vector<char>>& board) {
        for(int row = 0; row < board.size(); row++) {
            for (int col = 0; col < board[0].size(); col++){
                if (board[row][col] == '.'){
                    for (char k = '1'; k <= '9'; k++) {
                        if(isValid(row, col, k, board)) {
                            board[row][col] = k;
                            if (backtracking(board)) return true;
                            board[row][col] = '.';
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

    bool isValid(int row, int col, char k, vector<vector<char>>& board) {
        // row[0, 8]  col[0, 8]
        // 检查行
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == '.') continue;
            if (board[row][i] == k) return false;
        }

        // 检查列
        for (int i = 0; i < 9; i++) {
            if (board[i][col] == '.') continue;
            if (board[i][col] == k) return false;
        }

        // 检查3x3
        int startRow = 3 * (row / 3);
        int startCol = 3 * (col / 3);
        for (int i = startRow; i < startRow + 3; i++){
            for (int j = startCol; j < startCol + 3; j++){
                if (board[i][j] == '.') continue;
                if (board[i][j] == k) return false;
            }
        }
        
        return true;
    }

public:
    void solveSudoku(vector<vector<char>>& board) {
        backtracking(board);
    }
};
// @lc code=end

