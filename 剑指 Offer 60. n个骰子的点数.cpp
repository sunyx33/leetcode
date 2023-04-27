class Solution {
public:
    vector<double> dicesProbability(int n) {
        vector<double> dp(6, 1 / 6.0);
        for(int i = 2; i <= n; i++) {
            vector<double> tmp(5 * i + 1, 0);
            for(int j = 0; j < dp.size(); j++) {
                for(int k = 0; k < 6; k++) {
                    tmp[k + j] += dp[j] / 6.0;
                }
            }
            dp = tmp;
        }
        return dp;
    }
};