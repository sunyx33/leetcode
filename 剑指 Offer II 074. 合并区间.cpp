class Solution {
public:
    static bool cmp(vector<int>& a, vector<int>& b) {
        return a[0] < b[0];
    }
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), cmp);
        vector<vector<int>> result;
        result.push_back(intervals[0]);
        for(vector<int> vec : intervals) {
            if(vec[0] <= result.back()[1]) {
                result.back()[1] = max(result.back()[1], vec[1]);
            } else result.push_back(vec);
        }
        return result;
    }
};