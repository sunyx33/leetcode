class Solution {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        int k = 0;
        for(int num : nums) {
            k ^= num;
        }

        int m = 1;
        while((m & k) == 0) {
            m <<= 1;
        }

        int a = 0;
        int b = 0;
        for(int num : nums) {
            if((num & m) == 0) {
                a ^= num;
            } else {
                b ^= num;
            }
        }
        return {a, b};
    }
};