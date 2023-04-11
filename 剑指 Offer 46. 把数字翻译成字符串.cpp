class Solution {
public:
    int translateNum(int num) {
        string s = to_string(num);
        if (s.size() == 1) return 1;
        vector<int> dp(2);
        dp[0] = 1;
        if (s[0] == 49 || (s[0] == 50 && s[1] < 54)) dp[1] = 2;
        else dp[1] = 1;
        for (int i = 2; i < s.size(); i++) {
            if (s[i - 1] == 49 || (s[i - 1] == 50 && s[i] < 54)) {
                int sum = dp[1] + dp[0];
                dp[0] = dp[1];
                dp[1] = sum;
            } else {
                dp[0] = dp[1];
            }
        }
        return dp[1];
    }
};