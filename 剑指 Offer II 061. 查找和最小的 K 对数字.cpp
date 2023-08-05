class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<vector<int>> ans;
        auto cmp = [&nums1, &nums2](vector<int>& p1, vector<int>& p2) {
            return nums1[p1[0]] + nums2[p1[1]] > nums1[p2[0]] + nums2[p2[1]];
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> heap(cmp);
        for(int i = 0; i < min(k, static_cast<int>(nums1.size())); i++) {
            heap.push(vector<int> {i, 0});
        }
        while(k -- && !heap.empty()) {
            vector<int> vec = heap.top();
            ans.push_back(vector<int> {nums1[vec[0]], nums2[vec[1]]});
            heap.pop();
            if(vec[1] + 1 < nums2.size()){
                heap.push(vector<int> {vec[0], vec[1] + 1});
            }
        }
        return ans;
    }
};