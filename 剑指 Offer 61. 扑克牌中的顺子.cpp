class Solution {
public:
    bool isStraight(vector<int>& nums) {
        unordered_set<int> set;
        int minN = 14;
        int maxN = 0;
        for(int num : nums) {
            if (num == 0) continue;
            else if(set.find(num) == set.end()) set.emplace(num);
            else return false;
            minN = min(minN, num);
            maxN = max(maxN, num);
        }
        return maxN - minN < 5;
    }
};