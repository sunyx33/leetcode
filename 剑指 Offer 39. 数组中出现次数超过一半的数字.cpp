class Solution {
public:
    int majorityElement(vector<int>& nums) {
        // unordered_map<int, int> map;
        // int result = nums[0];
        // for(int num : nums) {
        //     if(map.find(num) == map.end()) map.emplace(num, 1);
        //     else map[num] ++;
        //     if(map[num] > nums.size() / 2) result = num;
        // }
        // return result;
        int res = 0, count = 0;
        for(int i = 0; i < nums.size(); i++) {
            if(count == 0) {
                res = nums[i];
                count ++;
            }
            else res == nums[i] ? count ++ : count --;
        }
        return res;
    }
};