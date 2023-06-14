class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> uMap;
        uMap[0] = 1;
        int sum = 0;
        int res = 0;
        for(int n : nums) {
            sum += n;
            if(uMap.find(sum - k) != uMap.end()) {
                res += uMap[sum - k];
            }
            uMap[sum] ++;
        }
        return res;
    }
};