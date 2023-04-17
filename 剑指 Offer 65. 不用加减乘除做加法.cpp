class Solution {
public:
    int add(int a, int b) {
        int sum = a;
        while(b != 0) {
            sum = a ^ b;
            b = (unsigned int)(a & b) << 1;
            a = sum;
        }
        return sum;
    }
};