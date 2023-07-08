class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        set<int> window;
        for(int i = 0; i < nums.size(); i++) {
            auto iter  = window.lower_bound(max(nums[i], INT_MIN + t) - t);
            if(iter != window.end() && *iter <= min(nums[i], INT_MAX - t) + t) return true;
            window.emplace(nums[i]);
            if(i >= k) {
                window.erase(nums[i - k]);
            }
        }
        return false;
    }
};