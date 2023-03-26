class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
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