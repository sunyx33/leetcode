class Solution {
public:
    int cuttingRope(int n) {
        if (n == 2) return 1;
        if (n == 3) return 2;
        if (n == 4) return 4;
        long long res = 1;
        while (n > 4) {
            n -= 3;
            res = res * 3 % 1000000007;
        }
        res = res * n % 1000000007;
        return (int) res;
    }
};