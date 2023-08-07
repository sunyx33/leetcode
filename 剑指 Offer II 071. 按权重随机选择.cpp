class Solution {
public:
    vector<int> vec;
    Solution(vector<int>& w) {
        partial_sum(w.begin(), w.end(), back_inserter(vec));
    }
    
    int pickIndex() {
        return upper_bound(vec.begin(), vec.end(), rand() % vec.back()) - vec.begin();
    }
};