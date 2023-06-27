class Solution {
public:
    int maximalRectangle(vector<string>& matrix) {
        int result = 0;
        if(matrix.size() == 0) return result;
        vector<int> heights(matrix[0].size(), 0);
        for(int i = 0; i < matrix.size(); i++) {
            for(int j = 0; j < matrix[i].size(); j++) {
                if(matrix[i][j] == '0') heights[j] = 0;
                else heights[j] ++;
            }
            result = max(result, maxRec1D(heights));
        }
        return result;
    }

    int maxRec1D(vector<int>& heights) {
        stack<int> sta;
        heights.insert(heights.begin(), 0);
        heights.push_back(0);
        sta.push(0);
        int result = 0;
        for(int i = 1; i < heights.size(); i++) {
            if(heights[sta.top()] < heights[i]) {
                sta.push(i);
            } else if(heights[sta.top()] == heights[i]) {
                sta.pop();
                sta.push(i);
            } else {
                while(heights[sta.top()] > heights[i]) {
                    int h = heights[sta.top()];
                    sta.pop();
                    int w = i - sta.top() - 1;
                    int area = h * w;
                    result = max(result, area);
                }
                sta.push(i);
            }
        }
        heights.pop_back();
        heights.erase(heights.begin());
        return result;
    }
};