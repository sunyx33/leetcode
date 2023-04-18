class Solution {
public:
    int singleNumber(vector<int>& nums) {
        vector<int> ones(32);
        for(int num : nums) {
            for(int j = 0; j < 32; j++) {
                ones[j] += num & 1;
                num >>= 1;
            }
        }
        int res = 0;
        for(int i = 0; i < 32; i++) {
            res |= (ones[i] % 3) <<i;
        }
        return res;
    }
};