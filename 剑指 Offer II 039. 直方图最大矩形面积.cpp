class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> sta;
        heights.insert(heights.begin(), 0);
        heights.push_back(0);
        sta.push(0);
        int result = 0;
        for(int i = 1;i < heights.size(); i++) {
            if(heights[i] > heights[sta.top()]) sta.push(i);
            else if(heights[i] == heights[sta.top()]) {
                sta.pop();
                sta.push(i);
            }
            else {
                while(heights[i] < heights[sta.top()]){
                    int height = heights[sta.top()];
                    sta.pop();
                    int wide = i - sta.top() - 1;
                    int area = height * wide;
                    if(area > result) result = area;
                }
                sta.push(i);
            }
        }
        return result;
    }
};