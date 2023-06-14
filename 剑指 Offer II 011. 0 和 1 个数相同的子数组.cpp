class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int result = 0;
        int sum = 0;
        unordered_map<int, int> uMap;
        uMap[0] = -1;
        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] == 0) sum += -1;
            else sum += 1;
            if(uMap.find(sum) != uMap.end()) {
                result = max(result, i - uMap.find(sum)->second);
                continue;
            }
            uMap[sum] = i;
        }
        return result;
    }
};